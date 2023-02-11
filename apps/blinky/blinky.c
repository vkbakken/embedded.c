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
        for (uint32_t i = 0; i < 32000000; ++i) { ; }
        board_led_on(0);
        for (uint32_t i = 0; i < 32000000; ++i) { ; }
    }
}
