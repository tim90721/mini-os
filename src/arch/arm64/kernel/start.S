#define INIT_STACK_SIZE		4096

	.align 6
_init_stack:
	.rept	INIT_STACK_SIZE * 8
	.byte 0
	.endr

	.text
	.align 3
	.global _start
_start:
	/* we only use 1 CPU right now. put other CPUs to __park. */
	mrs	x9, mpidr_el1
	and	x9, x9, #0xFF
	cbnz	x9, __park

bss_init:
	adrp	x10, __bss_start
	add	x10, x10, #:lo12:__bss_start
	adrp	x11, __bss_end
	add	x11, x11, #:lo12:__bss_end

	/* check need to clear 1 byte */
	and	x12, x11, #0x1
	cbz	x12, 1f

	/* clear 1 byte */
	strb	wzr, [x11, #-1]!

1:
	/* check need to clear 2 bytes */
	and	x12, x11, #0x2
	cbz	x12, 1f

	/* clear 2 bytes */
	strh	wzr, [x11, #-2]!

1:
	/* check need to clear 4 bytes */
	and	x12, x11, #0x4
	cbz	x12, 1f

	/* clear 4 bytes */
	strb	wzr, [x11, #-4]!

1:
	/* clear 8 bytes for the rest */
	cmp	x10, x11
	b.eq	prepare_init_stack
	str	xzr, [x10], #8
	b	1b

prepare_init_stack:
	lsl	x9, x9, 12
	ldr	x11, =_init_stack
	add	x11, x11, x9
	add	sp, x11, #INIT_STACK_SIZE

	/* jump to start kernel */
	bl	start_kernel

__park:
	wfi
	b	__park

	.end
