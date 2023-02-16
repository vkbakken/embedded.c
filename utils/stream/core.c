#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <interrupt.h>
#include <stream.h>
#include <utils/ring.h>
#include <util.h>


enum conversion_state {
	//! \internal Normal state, passing characters through to the console.
	STATE_NORMAL,
	//! \internal Parsing an optional conversion flag.
	STATE_FLAG,
	//! \internal Parsing an optional field width specifier.
	STATE_WIDTH,
	//! \internal Looking for a period indicating a precision specifier.
	STATE_PERIOD,
	//! \internal Parsing an optional precision specifier.
	STATE_PRECISION,
	//! \internal Parsing an optional length modifier.
	STATE_LENGTH,
	//! \internal Parsing the conversion specifier.
	STATE_CONVSPEC,
};


struct printf_conversion {
	//! Minimum field width, or 0 if unspecified.
	int width;
	//! Minimum precision, or 0 if unspecified.
	int precision;
	//! Length modifier. This can be 'h', 'l' or 0 (default.)
	char length;
	//! Conversion specifier.
	char spec;
	//! Character to use for padding to specified width
	char pad_char;
	//! Conversion argument extracted from \a ap.
	union {
		//! Signed integer argument.
		long d;
		//! Unsigned integer argument.
		unsigned long u;
		//! Floating-point argument.
		double f;
		//! String argument.
		const char *s;
		//! Pointer argument.
		void *p;
		//! Where to store the result of a %n conversion.
		int *n;
	} arg;
};


static void stream_priv_write_universal(struct stream *stream,
		const char *data, size_t len)
{
	size_t partial;
	unsigned int head;
	irqflags_t iflags;

	while (len) {
		if (stream_buf_unused(stream) < len) {
			if (!stream->make_room(stream, len))
				return;
		}

		iflags = cpu_irq_save();
		head = stream_buf_head(stream);
		partial = min_u(len, stream_buf_unused_before_end(stream));
		memcpy(&stream->data[head], data, partial);
		ring_insert_entries(&stream->ring, partial);
		cpu_irq_restore(iflags);

		data += partial;
		len -= partial;
	}
}

static void stream_priv_write(struct stream *stream,
		const char *data, size_t len)
{
	stream_priv_write_universal(stream, data, len);
}


static int stream_priv_putchar(struct stream *stream, char c)
{
	if (c == '\n')
		stream_priv_putchar(stream, '\r');

	stream_priv_write(stream, &c, 1);

	return c;
}


static int stream_priv_putstr(struct stream *stream, const char *str)
{
	int len;

	len = strlen(str);
	stream_priv_write(stream, str, len);

	return len;
}


static void stream_priv_commit(struct stream *stream)
{
	stream->commit(stream);
}


static int stream_priv_print_signed(struct stream *stream,
		struct printf_conversion *conv)
{
	char buf[32];
	long number = conv->arg.d;
	bool negative = false;
	int i = sizeof(buf);
	int len;
	char c;

	if (number == 0)
		buf[--i] = '0';

	if (number < 0) {
		negative = true;
		number = -number;
	}

	while (number) {
		c = '0' + number % 10;
		number /= 10;
		buf[--i] = c;
	}

	if (negative)
		buf[--i] = '-';

	if (conv->width > sizeof(buf))
		conv->width = sizeof(buf);

	while ((sizeof(buf) - i) < conv->width)
		buf[--i] = conv->pad_char;

	len = sizeof(buf) - i;
	stream_priv_write(stream, buf + i, len);

	return len;
}


static int stream_priv_print_unsigned(struct stream *stream,
		struct printf_conversion *conv)
{
	char buf[32];
	unsigned long number = conv->arg.u;
	int i = sizeof(buf);
	int len;
	char c;

	if (number == 0)
		buf[--i] = '0';

	switch (conv->spec) {
	case 'o':
		while (number) {
			c = '0' + (number & 7);
			number >>= 3;
			buf[--i] = c;
		}
		break;
	case 'u':
		while (number) {
			c = '0' + (number % 10);
			number /= 10;
			buf[--i] = c;
		}
		break;
	case 'x':
		while (number) {
			if ((number & 15) > 9)
				c = 'a' - 10 + (number & 15);
			else
				c = '0' + (number & 15);
			number >>= 4;
			buf[--i] = c;
		}
		break;
	case 'X':
		while (number) {
			if ((number & 15) > 9)
				c = 'A' - 10 + (number & 15);
			else
				c = '0' + (number & 15);
			number >>= 4;
			buf[--i] = c;
		}
		break;
	}

	if (conv->width > sizeof(buf))
		conv->width = sizeof(buf);

	while ((sizeof(buf) - i) < conv->width)
		buf[--i] = conv->pad_char;

	len = sizeof(buf) - i;
	stream_priv_write(stream, buf + i, len);

	return len;
}


int stream_putstr(struct stream *stream, const char *str)
{
	int len;

	len = stream_priv_putstr(stream, str);
	stream_priv_commit(stream);

	return len;
}


int stream_putchar(struct stream *stream, int c)
{
	c = stream_priv_putchar(stream, c);
	stream_priv_commit(stream);

	return c;
}

static int stream_priv_vprintf(struct stream *stream,
		const char *format, va_list ap)
{
	int state = STATE_NORMAL;
	struct printf_conversion conv;
	int n = 0;
	char c;

	while (true) {
		c = *format++;

		if (!c)
			break;

		switch (state) {
		case STATE_NORMAL:
			if (c == '%') {
				state = STATE_FLAG;
				conv.width = 0;
				conv.precision = 0;
				conv.length = 0;
				conv.pad_char = ' ';
			} else {
				stream_priv_putchar(stream, c);
				n++;
			}
			break;

		case STATE_FLAG:
			state = STATE_WIDTH;

			/* We accept all standard flags, but we ignore some */
			switch (c) {
			case '0':
				conv.pad_char = '0';
				break;
			case '#':
			case '-':
			case ' ':
			case '+':
				break;

			case '%':
				/* %% -> output a literal '%' */
				stream_priv_putchar(stream, c);
				n++;
				state = STATE_NORMAL;
				break;

			default:
				goto state_width;
			}
			break;

		state_width:
		case STATE_WIDTH:
			if (isdigit(c) && (c != '0' || conv.width != 0)) {
				conv.width *= 10;
				conv.width += c - '0';
				break;
			}

			state = STATE_PERIOD;
			/* fall through */

		case STATE_PERIOD:
			if (c != '.') {
				state = STATE_LENGTH;
				goto state_length;
			}
			state = STATE_PRECISION;
			break;

		case STATE_PRECISION:
			/* accept but ignore */
			if (isdigit(c))
				break;

			state = STATE_LENGTH;
			/* fall through */

		state_length:
		case STATE_LENGTH:
			/* SUSv2 only accepts h, l and L */
			if (c == 'h' || c == 'l' || c == 'L') {
				conv.length = c;
				break;
			} else if (c == 'z') {
				if (sizeof(size_t) == sizeof(long))
					conv.length = 'l';
				break;
			}

			state = STATE_CONVSPEC;
			/* fall through */

		case STATE_CONVSPEC:
			conv.spec = c;

			switch (c) {
			case 'd':
			case 'i':
				if (conv.length == 'l')
					conv.arg.d = va_arg(ap, long);
				else
					conv.arg.d = va_arg(ap, int);
				n += stream_priv_print_signed(stream, &conv);
				break;
			case 'o':
			case 'u':
			case 'x':
			case 'X':
				if (conv.length == 'l')
					conv.arg.u = va_arg(ap, unsigned long);
				else
					conv.arg.u = va_arg(ap, unsigned int);
				n += stream_priv_print_unsigned(stream, &conv);
				break;
			case 'c':
				conv.arg.d = va_arg(ap, int);
				stream_priv_putchar(stream, conv.arg.d);
				n++;
				break;

			/* TODO: Handle floats if needed */

			case 'S':
				/* fall through */
			case 's':
				conv.arg.s = va_arg(ap, const char *);
				n += stream_priv_putstr(stream, conv.arg.s);
				break;
			case 'p':
				conv.arg.p = va_arg(ap, void *);
				stream_priv_write(stream, "0x", 2);
				n += 2;
				conv.spec = 'x';
				n += stream_priv_print_unsigned(stream, &conv);
				break;
			case 'n':
				conv.arg.n = va_arg(ap, int *);
				*conv.arg.n = n;
				break;
			}

			state = STATE_NORMAL;
			break;
		}
	}

	stream_priv_commit(stream);

	return n;
}


int stream_vprintf(struct stream *stream, const char *format, va_list ap)
{

	return stream_priv_vprintf(stream, format, ap);
}


int stream_printf(struct stream *stream, const char *format, ...)
{
	int n;
	va_list ap;

	va_start(ap, format);
	n = stream_vprintf(stream, format, ap);
	va_end(ap);

	return n;
}


void stream_init(struct stream *s, char *mem, uint16_t size)
{   
    s->data = mem;
    *(unsigned int *)&s->ring_mask = size - 1;
}


void stream_worker(struct stream *s)
{

}
