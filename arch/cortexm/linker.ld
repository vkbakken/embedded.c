MEMORY
{
	flash   (rx)  : ORIGIN = 0x00000000, LENGTH = 1M
	sram    (rwx) : ORIGIN = 0x20000000, LENGTH = 256K
}


OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm",
	      "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)


SECTIONS
{
	. = ORIGIN(flash);
	.text : {
		. = ALIGN(4);
    	KEEP(*(.vec_tbl))     	 /* Vector table early in memory*/
		. = ALIGN(4);
    	KEEP(*(.start))     	 /* Start up code early in memory*/
    	*(.text)                 /* .text sections (code) */
    	*(.text*)                /* .text* sections (code) */
		*(.rodata)               /* .rodata sections (constants, strings, etc.) */
    	*(.rodata*)              /* .rodata* sections (constants, strings, etc.) */
	} > flash

	. = .;
	. = ALIGN(4);
    __etext = .;

	.data : AT (__etext)
	{
		. = ALIGN(4);
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
