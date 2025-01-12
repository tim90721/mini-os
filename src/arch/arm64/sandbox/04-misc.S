
	.data
	.align 3

	.text
	.align 3
	.global _start
_start:
_adr_adrp_test:
	adr	x0,	test_data1	// adr xd, <label>
					// load an address of a label relative
					// to PC +-1MB
	adrp	x1,	test_data1	// adrp xd, <label>
					// load an address of a label relative
					// to PC +-4GB. The result will be
					// aligned to 4KB

	adr	x2,	test_data2
	adrp	x3,	test_data2

	add	x3,	x3,	#:lo12:test_data2
	// compiler specific support to relocation, check following link
	// https://sourceware.org/binutils/docs-2.29/as/AArch64_002dRelocations.html

_mrs_msr_test:
	mrs	x4,	CurrentEL
	mrs	x5,	daif		// Debug, SError, IRQ, FIQ
	mrs	x6,	nzcv
	mrs	x8,	spsel		// 0: to use EL0 SP, 1: to use ELx SP
	mrs	x10,	sctlr_el1	// M[0:0]  :	enable MMU
					// C[2:2]  :	enable data cache
					// I[12:12]:	enable instruction cache

stop:
1:
	b 1b

test_data1:
	.int	5
test_data2:
	.int	6

	.end
