#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED


#include <stdbool.h>


//! \name Transmitting Data
//@{
/**
 * \brief Send a string to the UART
 *
 * \param uart_id UART id.
 * \param data String to be sent.
 */
#define uart_put_string(uart_id, data)					\
	do {								\
		unsigned int i;						\
		for (i = 0; data[i] != 0; i++) {			\
			while (!uart_put_byte(uart_id, data[i]));	\
		}							\
	} while (0)

/**
 * \brief Send a given number of bytes to the UART
 *
 * \param uart_id UART id.
 * \param data bytes to be sent.
 * \param len the number of bytes to be sent.
 */
#define uart_put_bytes(uart_id, data, len)				\
	do {								\
		unsigned int i;						\
		for (i = 0; i < len; i++) {				\
			while (!uart_put_byte(uart_id, data[i]));	\
		}							\
	} while (0)
#endif /*UART_H_ENABLED*/
