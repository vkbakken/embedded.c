#ifndef CTRL_UART_H_INCLUDED
#define CTRL_UART_H_INCLUDED


#define UART_FLAG_RX		(1 << 0)
#define UART_FLAG_TX		(1 << 1)


#if defined(CONFIG_ARCH_POSIX)
# include <uart/ctrl_posix.h>
#endif

void uart_ctrl_init_defaults(uint8_t id);
void uart_enable(uint8_t id, unsigned int flags);

bool uart_put_byte_priv(uint8_t id, uint8_t data);
#endif /*CTRL_UART_H_INCLUDED*/
