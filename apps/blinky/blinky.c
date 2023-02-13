#include <stdint.h>
#include <stdbool.h>

#include <board/init.h>
#include <board/led.h>
#include <delay.h>


int main(void)
{
    board_init();
    while (true) {
        board_led_off(0);
        mdelay(1000);
        board_led_on(0);
        mdelay(1000);
    }
}
