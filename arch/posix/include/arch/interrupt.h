#ifndef INTERRUPT_ARCH_POSIX_H_INCLUDED
#define INTERRUPT_ARCH_POSIX_H_INCLUDED


#include <stdint.h>
#include <compiler.h>


typedef uint32_t irqflags_t;


#define cpu_irq_enable()                            \
	do {                                            \
		barrier();                              	\
	} while (0)


#define cpu_irq_disable()                           \
	do {                                            \
		barrier();                                  \
	} while (0)


__always_inline static irqflags_t cpu_irq_save(void)
{
	irqflags_t flags;

	cpu_irq_disable();

	return flags;
}


__always_inline static void cpu_irq_restore(irqflags_t flags)
{
	barrier();
}


__always_inline static bool cpu_irq_is_enabled_flags(irqflags_t flags)
{
	return (flags & 0x1);
}


__always_inline static bool cpu_irq_is_enabled(void)
{
	irqflags_t flags;

	return cpu_irq_is_enabled_flags(flags);
}
#endif /*INTERRUPT_ARCH_POSIX_H_INCLUDED*/
