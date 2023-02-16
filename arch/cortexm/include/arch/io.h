#ifndef IO_ARCH_CORTEXM_H_INCLUDED
#define IO_ARCH_CORTEXM_H_INCLUDED


#include <stdint.h>


static inline uint8_t mmio_read8(const void *p)
{
	return *(const volatile uint8_t *)p;
}


static inline uint16_t mmio_read16(const void *p)
{
	return *(const volatile uint16_t *)p;
}


static inline uint32_t mmio_read32(const void *p)
{
	return *(const volatile uint32_t *)p;
}


static inline void mmio_write8(void *p, uint8_t val)
{
	*(volatile uint8_t *)p = val;
}


static inline void mmio_write16(void *p, uint16_t val)
{
	*(volatile uint16_t *)p = val;
}


static inline void mmio_write32(void *p, uint32_t val)
{
	*(volatile uint32_t *)p = val;
}
#endif /*IO_ARCH_CORTEXM_H_INCLUDED*/
