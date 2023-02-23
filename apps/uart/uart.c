#include <stdint.h>
#include <stdbool.h>

#include <arch/irq.h>
#include <delay.h>
#include <init.h>
#include <led.h>
#include <uart.h>


#define DEBUG_UART          CONFIG_DEBUG_UART



INTC_DEFINE_HANDLER(20, test_entry);


void test_entry(void)
{
    while (1) { ;}
}


int main(void)
{
    board_init();

    uart_ctrl_init_defaults(DEBUG_UART);
	uart_enable(DEBUG_UART, UART_FLAG_TX | UART_FLAG_TX);
    
    while (true) {
        board_led_off(0);
        uart_put_byte(0, 'O');
        mdelay(1000);
        board_led_on(0);
        uart_put_byte(0, 'o');
        mdelay(1000);
    }

    return 0;
}
