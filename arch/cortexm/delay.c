#include <stdint.h>
#include <stdbool.h>

#include <clk/sys.h>
#include <delay.h>
#include <io.h>
#include <util.h>


#define DEMCR_TRCENA    0x01000000

/* Core Debug registers */
#define DEMCR           (*((volatile uint32_t *)0xE000EDFC))
#define DWT_CTRL        (*(volatile uint32_t *)0xe0001000)
#define CYCCNTENA       (1<<0)
#define DWT_CYCCNT      ((volatile uint32_t *)0xE0001004)
#define CPU_CYCLES      *DWT_CYCCNT


#define DWT_BASE        (0xE0000000U + 0x1000)


void udelay(unsigned int us)
{
    uint32_t count, count_end;

	count = mmio_read32((void *)(DWT_BASE + 0x4));
	count_end = count + div_ceil(sysclk_get_cpu_hz(), 1000000) * us;

	while ((int32_t)(count_end - count) > 0) {
        count = mmio_read32((void *)(DWT_BASE + 0x4));
    }
}


void mdelay(unsigned int ms)
{
    while (ms) {
        udelay(1000);
        --ms;
    }
}
