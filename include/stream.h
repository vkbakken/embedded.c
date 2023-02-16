#ifndef STREAM_H_INCLUDED
#define STREAM_H_INCLUDED


#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <assert.h>
#include <types.h>
#include <utils/ring.h>


struct stream {
    struct ring_head    ring;
	const unsigned int	ring_mask;
    void (*commit)(struct stream *stream);
	bool (*make_room)(struct stream *stream, unsigned int goal);
	char                *data;
};


int stream_vprintf(struct stream *stream, const char *format, va_list ap);
int stream_printf(struct stream *stream, const char *format, ...)
	__printf_format(2, 3);
int stream_putstr(struct stream *stream, const char *str);
int stream_putchar(struct stream *stream, int c);

int snprintf(char *str, size_t size, const char *format, ...)
	__printf_format(3, 4);
int sprintf(char *str, const char *format, ...) __printf_format(2, 3);



static inline unsigned int stream_buf_size(struct stream *stream)
{
	return stream->ring_mask + 1;
}


static inline bool stream_buf_has_data(struct stream *stream)
{
	return !ring_is_empty(&stream->ring);
}


static inline bool stream_buf_is_full(struct stream *stream)
{
	return ring_is_full(&stream->ring, stream_buf_size(stream));
}


static inline unsigned int stream_buf_unused(struct stream *stream)
{
	return ring_entries_unused(&stream->ring, stream_buf_size(stream));
}


static inline unsigned int stream_buf_used(struct stream *stream)
{
	return ring_entries_used(&stream->ring);
}


static inline unsigned int stream_buf_unused_before_end(struct stream *stream)
{
	return ring_entries_unused_before_end(&stream->ring,
			stream_buf_size(stream));
}


static inline unsigned int stream_buf_used_before_end(struct stream *stream)
{
	return ring_entries_used_before_end(&stream->ring,
			stream_buf_size(stream));
}


static inline unsigned int stream_buf_head(struct stream *stream)
{
	return ring_get_head(&stream->ring, stream_buf_size(stream));
}


static inline unsigned int stream_buf_tail(struct stream *stream)
{
	return ring_get_tail(&stream->ring, stream_buf_size(stream));
}


static inline char stream_buf_insert_char(struct stream *stream, char c)
{
	assert(!stream_buf_is_full(stream));

	stream->data[stream_buf_head(stream)] = c;
	ring_insert_entries(&stream->ring, 1);

	return c;
}


static inline char stream_buf_extract_char(struct stream *stream)
{
	char	c;

	assert(stream_buf_has_data(stream));

	c = stream->data[stream_buf_tail(stream)];
	ring_extract_entries(&stream->ring, 1);

	return c;
}

void stream_init(struct stream *s, char *mem, uint16_t size);
void stream_worker(struct stream *s);
#endif /*STREAM_H_INCLUDED*/
