#include <stdint.h>


extern unsigned int __etext;
extern unsigned int __data_start__;
extern unsigned int __bss_start__;
extern unsigned int __bss_end__;
extern unsigned int __stack;


extern int main(void) __attribute__ ((weak, alias("default_fault_handler"), used));
static void default_fault_handler(void);
void _start(void) __attribute__ ((naked, section (".start")));


extern void nmi(void) __attribute__ ((weak, alias("default_fault_handler")));
extern void hard_fault(void) __attribute__ ((weak, alias("default_fault_handler")));
extern void memory_manage_fault(void) __attribute__ ((weak, alias("default_fault_handler")));
extern void bus_fault(void) __attribute__ ((weak, alias("default_fault_handler")));
extern void usage_fault(void) __attribute__ ((weak, alias("default_fault_handler")));
extern void sv_call(void) __attribute__ ((weak, alias("default_fault_handler")));
extern void debug_monitor(void) __attribute__ ((weak, alias("default_fault_handler")));
extern void pend_sv(void) __attribute__ ((weak, alias("default_fault_handler")));
extern void systick(void) __attribute__ ((weak, alias("default_fault_handler")));


/*Fault and interrupt table*/
const unsigned int __boot_exceptions[] __attribute__ ((section (".vec_tbl"), used)) = {
	[0] =	(unsigned int)&__stack,
    [1] =	(unsigned int)_start,
	[2] =	(unsigned int)nmi,
	[3] =	(unsigned int)hard_fault,
	[4] =	(unsigned int)memory_manage_fault,
	[5] =	(unsigned int)bus_fault,
	[6] =	(unsigned int)usage_fault,
	[11] =	(unsigned int)sv_call,
	[12] =	(unsigned int)debug_monitor,
	[14] =	(unsigned int)pend_sv,
	[15] =	(unsigned int)systick,
	//[16]=	(unsigned int)irq[NVIC_IRQ_COUNT]
};


void _start(void)
{
	/*At this point it is assumed that the CPU has been reset, either from power-on
	 * or in some other way. Interrupts and CPU in virgin state assumed.
	 */
	asm volatile (	"ldr		r0, =__stack\n" 
					"msr		psp, r0");

	/*Copy initialized data*/
	unsigned int *src = &__etext;
	unsigned int *dst = &__data_start__;
	unsigned int *end = &__bss_start__;

	while (dst != end) {
		*(dst++) = *(src++);
	}

	/*Clear BSS*/
	dst = &__bss_start__;
	end = &__bss_end__;
	while (dst != end) {
		*(dst++) = 0;
	}

	/*Jump to main*/
	main();

	/*If main was ever to return we stop here.*/
	__asm volatile( "cpsid i" ::: "memory" );
	while (1) { ; }
}


static void default_fault_handler(void)
{
	/*Interrupts off!*/
	__asm volatile( "cpsid i" ::: "memory" );
	while (1) { ; }
}
