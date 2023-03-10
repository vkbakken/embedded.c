#include <stdint.h>


extern unsigned int __etext;
extern unsigned int __data_start__;
extern unsigned int __bss_start__;
extern unsigned int __bss_end__;
extern unsigned int __stack;


static void _start(void) __attribute__ ((naked, section (".startup_code")));


int __attribute__((weak)) main(void)
{
	while (1) {
		;
	}
}



static void _start(void)
{
    /*Set the stack pointer*/
    asm volatile  (
		"la    gp, __global_pointer$;"
        "la    sp, __stack;"
	);

	/*At this point it is assumed that the CPU has been reset, either from power-on
	 * or in some other way. Interrupts and CPU in virgin state assumed.
	 */

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
	//__asm volatile( "cpsid i" ::: "memory" );
	while (1) { ; }
}