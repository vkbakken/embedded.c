#ifndef CTRL_UART_H_INCLUDED
#define CTRL_UART_H_INCLUDED


#define UART_FLAG_RX		(1 << 0)
#define UART_FLAG_TX		(1 << 1)


#if defined(CONFIG_ARCH_POSIX)
# include <uart/ctrl_posix.h>
#endif

void uart_ctrl_init_defaults(void *uart);
void uart_enable(void *uart, unsigned int flags);
#endif /*CTRL_UART_H_INCLUDED*/
