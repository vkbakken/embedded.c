#include <stdint.h>
#include <stdbool.h>

#include "board/init.h"
#include "board/led.h"
#include "cpu/delay.h"


int main(void)
{
    board_init();
    while (true) {
        baord_led_tgl(0);
        delay_ms();
    }
}
