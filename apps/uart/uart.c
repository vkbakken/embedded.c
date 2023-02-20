#include <stdint.h>
#include <stdbool.h>

#include <init.h>
#include <uart.h>


#define DEBUG_UART          CONFIG_DEBUG_UART


int main(void)
{
    board_init();

    uart_ctrl_init_defaults(DEBUG_UART);
	uart_enable(DEBUG_UART, UART_FLAG_TX | UART_FLAG_TX);
    
    while (true) {
        uart_put_byte_priv(0, 'O');
    }

    return 0;
}
