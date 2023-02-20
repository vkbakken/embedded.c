#ifndef NVIC_CORTEXM_ARCH_H_INCLUDED
#define NVIC_CORTEXM_ARCH_H_INCLUDED


#include <stdint.h>
#include <stdbool.h>

#include <arch/io.h>


#define NVIC_BASE   (0xE0000000U + 0xE000 + 0x0100)


static inline void nvic_disable(uint8_t irqn)
{
    uint32_t group = irqn / 32;
    uint32_t bit_mask = 1 << (irqn % 32);

    mmio_write32((void *)(NVIC_BASE + 0x80 + 4 * group), bit_mask);    
}


static inline void nvic_enable(uint8_t irqn)
{
    uint32_t group = irqn / 32;
    uint32_t bit_mask = 1 << (irqn % 32);

    mmio_write32((void *)(NVIC_BASE + 0x0 + 4 * group), bit_mask);
}


static inline void nvic_set_priority(uint8_t irqn, uint8_t priority)
{
}


static inline void nvic_clear_pending(uint8_t irqn)
{
    uint32_t group = irqn / 32;
    uint32_t bit_mask = 1 << (irqn % 32);

    mmio_write32((void *)(NVIC_BASE + 0x180 + 4 * group), bit_mask);
}
#endif /*NVIC_CORTEXM_ARCH_H_INCLUDED*/
