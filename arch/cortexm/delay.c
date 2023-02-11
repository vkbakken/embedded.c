#include <stdint.h>
#include <stdbool.h>

#include <delay.h>


void udelay(unsigned int us)
{
    volatile unsigned int ticks = 32000;

    while (ticks) {
        --ticks;
    }
}


void mdelay(unsigned int ms)
{
    while (ms) {
        udelay(1000);
        --ms;
    }
}