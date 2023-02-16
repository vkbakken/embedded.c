#ifndef UART_POSIX_UART_H_INCLUDED
#define UART_POSIX_UART_H_INCLUDED


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>


static inline bool uart_tx_buffer_is_empty(void *uart)
{
    return true;
}


static inline bool uart_put_byte(void *uart, uint8_t data)
{
    putchar(data);
	return true;
}
#endif /*UART_POSIX_UART_H_INCLUDED*/
