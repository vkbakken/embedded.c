#include <stdint.h>
#include <stdbool.h>

#include "board/led.h"
#include "chip/io.h"


void board_led_off(uint8_t led_no)
{
    switch (led_no) {
        case 0:
            NRF_P0->OUTSET = (1 << 13);
        break;
    }
}


void board_led_on(uint8_t led_no)
{
    switch (led_no) {
        case 0:
            NRF_P0->OUTCLR = (1 << 13);
        break;
    }
}
