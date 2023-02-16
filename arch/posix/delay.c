#include <stdint.h>
#include <stdbool.h>
#include<unistd.h>


#include <delay.h>


void udelay(unsigned int us)
{
    sleep(0.1);
}


void mdelay(unsigned int ms)
{
    while (ms) {
        udelay(1000);
        --ms;
    }
}
