#include <stdint.h>
#include <stdbool.h>


#include <delay.h>
#include <init.h>
#include <led.h>


int main(void)
{
    board_init();
    while (true) {
        board_led_off(0);
        mdelay(1000);
        board_led_on(0);
        mdelay(1000);
    }

    return 0;
}
