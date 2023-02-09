MEMORY
{
	flash   (rx)  : ORIGIN = 0x00020000, LENGTH = 8k
	sram   (rwx) : ORIGIN = 0x00020000, LENGTH = 8K
}


SECTIONS
{
	. = ORIGIN(flash);
	.text : {
		. = ALIGN(4);
    	KEEP(*(.startup_code))     /* Start up code early in memory*/
    	*(.text)                 /* .text sections (code) */
    	*(.text*)                /* .text* sections (code) */
		*(.rodata)               /* .rodata sections (constants, strings, etc.) */
    	*(.rodata*)              /* .rodata* sections (constants, strings, etc.) */
	} > sram


	. = .;
	. = ALIGN(4);
    __etext = .;
	.data : AT (__etext)
	{
		. = ALIGN(4);
      	__global_pointer$ = . + 2048;
      	__data_start__ = .;
      	__data_start = __data_start__;
      	*(.sdata* .sdata.* .gnu.linkonce.s.*)
      	*(.data*)

      	. = ALIGN(4);
      	__data_end__ = .;
	} > sram


	.bss : {
		. = ALIGN(4);
        __bss_start__ = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
        __bss_end__ = .;
	} > sram

    PROVIDE(__stack = ORIGIN(sram) + LENGTH(sram));
}
