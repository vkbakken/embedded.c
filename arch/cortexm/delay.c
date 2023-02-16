#include <stdint.h>
#include <stdbool.h>

#include <delay.h>


#define DEMCR_TRCENA    0x01000000

/* Core Debug registers */
#define DEMCR           (*((volatile uint32_t *)0xE000EDFC))
#define DWT_CTRL        (*(volatile uint32_t *)0xe0001000)
#define CYCCNTENA       (1<<0)
#define DWT_CYCCNT      ((volatile uint32_t *)0xE0001004)
#define CPU_CYCLES      *DWT_CYCCNT


static inline uint32_t stopwatch_getticks()
{
    return CPU_CYCLES;
}


static inline void stopwatch_delay(uint32_t ticks)
{
    uint32_t end_ticks = ticks + stopwatch_getticks();
    while(1)
    {
            if (stopwatch_getticks() >= end_ticks)
                    break;
    }
}


void udelay(unsigned int us)
{
    DEMCR |= DEMCR_TRCENA; 
    *DWT_CYCCNT = 0;             
    /* Enable CPU cycle counter */
    DWT_CTRL |= CYCCNTENA;

    volatile unsigned int ticks = 32 * us;

    stopwatch_delay(ticks);
}


void mdelay(unsigned int ms)
{
    while (ms) {
        udelay(1000);
        --ms;
    }
}
