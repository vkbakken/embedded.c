#include <assert.h>
#include <console.h>
#include <stream.h>
#include <uart.h>
#include <uart/ctrl.h>
#include <util.h>


#ifdef CONFIG_CONSOLE_BUF_SIZE
# define DEBUG_BUF_SIZE	CONFIG_DEBUG_CONSOLE_BUF_SIZE
#else
# define DEBUG_BUF_SIZE	64
#endif


static char	out_buffer[DEBUG_BUF_SIZE];


struct stream	out_stream = {
	.ring_mask	= DEBUG_BUF_SIZE - 1,
	.data		= out_buffer,
};


int dbg_vprintf(const char *format, va_list ap)
{
	return stream_vprintf(&out_stream, format, ap);
}


int dbg_printf(const char *format, ...)
{
	va_list ap;
	int n;

	va_start(ap, format);
	n = stream_vprintf(&out_stream, format, ap);
	va_end(ap);

	return n;
}


int dbg_putstr(const char *str)
{
	return stream_putstr(&out_stream, str);
}


int dbg_putchar(int c)
{
	return stream_putchar(&out_stream, c);
}


void console_init(void)
{
	build_assert(is_power_of_two(DEBUG_BUF_SIZE));
	dbg_backend_init(&out_stream);
}
