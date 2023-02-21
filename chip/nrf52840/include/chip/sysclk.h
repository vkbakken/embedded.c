#ifndef SYSCLK_CHIP_NRF52840_H_INCLUDED
#define SYSCLK_CHIP_NRF52840_H_INCLUDED


#include <stdint.h>


static inline uint32_t sysclk_get_cpu_hz(void)
{
	return 32000000UL;
}
#endif /*SYSCLK_CHIP_NRF52840_H_INCLUDED*/
