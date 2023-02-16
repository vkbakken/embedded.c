#ifndef INTERRUPT_ARCH_CORTEXM_H_INCLUDED
#define INTERRUPT_ARCH_CORTEXM_H_INCLUDED


#include <stdint.h>
#include <compiler.h>


typedef uint32_t irqflags_t;


#define cpu_irq_enable()                            \
	do {                                            \
		barrier();                              	\
		__asm volatile( "cpsie i" ::: "memory" );	\
	} while (0)


#define cpu_irq_disable()                               \
	do {                                            \
		__asm volatile( "cpsid i" ::: "memory" );     \
		barrier();                              \
	} while (0)


__always_inline static irqflags_t cpu_irq_save(void)
{
	irqflags_t flags;

	__asm__ volatile ("MRS %0, PRIMASK"  : "=r" (flags));
	cpu_irq_disable();

	return flags;
}


__always_inline static void cpu_irq_restore(irqflags_t flags)
{
	barrier();
	__asm__ __volatile__("MSR PRIMASK, %0" : : "r" (flags));
}


__always_inline static bool cpu_irq_is_enabled_flags(irqflags_t flags)
{
	return (flags & 0x1);
}


__always_inline static bool cpu_irq_is_enabled(void)
{
	irqflags_t flags;

	__asm__ volatile ("MRS %0, PRIMASK"  : "=r" (flags));
	return cpu_irq_is_enabled_flags(flags);
}
#endif /*INTERRUPT_ARCH_CORTEXM_H_INCLUDED*/
