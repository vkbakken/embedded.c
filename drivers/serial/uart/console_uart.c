#include <console.h>
#include <interrupt.h>
#include <stream.h>
#include <uart.h>
#include <uart/ctrl.h>


#define DEBUG_UART	CONFIG_DEBUG_UART_ID


static void dbg_commit(struct stream *stream)
{
	irqflags_t	iflags;
	char		c;

	iflags = cpu_irq_save();
	while (stream_buf_has_data(stream)) {
		c = stream_buf_extract_char(stream);

		while (!uart_put_byte(DEBUG_UART, c)) {
			cpu_irq_restore(iflags);
			while (!uart_tx_buffer_is_empty(DEBUG_UART))
				barrier();
			cpu_irq_disable();
		}
	}
	cpu_irq_restore(iflags);
}

static bool dbg_make_room(struct stream *stream, unsigned int goal)
{
	/* Keep it simple for now */
	dbg_commit(stream);

	/* We are always able to make room */
	return true;
}


void dbg_backend_init(struct stream *out)
{
	uart_ctrl_init_defaults(DEBUG_UART);
	uart_enable(DEBUG_UART, UART_FLAG_TX);

    out->make_room = dbg_make_room;
    out->commit = dbg_commit;
}
