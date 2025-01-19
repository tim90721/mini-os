MEMORY
{
	ram1(RX)	: ORIGIN = 0x40000000 LENGTH = 64M
	ram2(WI!R)	: ORIGIN = 0x44000000 LENGTH = 64M
}

OUTPUT_FORMAT("elf64-littleaarch64", "elf64-bigaarch64",
	      "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
ENTRY(_start)

SECTIONS
{
	.init : {
		*(.init)
	} > ram1

	.text : {
		. = ALIGN(16);
		__text_start = .;
		*(.text)
		*(.text.*)
		__text_end = .;
	} > ram1

	.rodata : {
		. = ALIGN(16);
		*(.rodata)
		*(.rodata.*)
	} > ram1

	.data : {
		. = ALIGN(16);
		__data_start = .;
		*(.data)
		*(.data.*)
		*(.sdata)
		*(.sdata.*)
		__data_end = .;
	} > ram2

	.bss (NOLOAD) : {
		. = ALIGN(16);
		__bss_start = .;
		*(.bss)
		*(.bss.*)
		*(.sbss)
		*(.sbss.*)
		__bss_end = .;
	} > ram2

	PROVIDE(__memory_start = ORIGIN(ram2));
	PROVIDE(__memory_end = ORIGIN(ram2) + LENGTH(ram2));

	PROVIDE(__heap_start = __bss_end);
	PROVIDE(__heap_size = __memory_end - __heap_start);
}
