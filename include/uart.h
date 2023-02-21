#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED


#include <stdbool.h>

#include <uart/ctrl.h>


#define uart_put_byte(uart_id, data)\
	uart_put_byte_priv(uart_id, data)


#define uart_put_string(uart_id, data)					\
	do {								\
		unsigned int i;						\
		for (i = 0; data[i] != 0; i++) {			\
			while (!uart_put_byte(uart_id, data[i]));	\
		}							\
	} while (0)


#define uart_put_bytes(uart_id, data, len)				\
	do {								\
		unsigned int i;						\
		for (i = 0; i < len; i++) {				\
			while (!uart_put_byte(uart_id, data[i]));	\
		}							\
	} while (0)
#endif /*UART_H_ENABLED*/
