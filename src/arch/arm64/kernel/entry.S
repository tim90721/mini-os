#include <generated/asm-offsets.h>

# explicitly not saving x10, x11 since they're corrupted right now
.macro reg_backup base
	stp		x0, x1, [\base, #TASK_CTX_X0]
	stp		x2, x3, [\base, #TASK_CTX_X2]
	stp		x4, x5, [\base, #TASK_CTX_X4]
	stp		x6, x7, [\base, #TASK_CTX_X6]
	stp		x8, x9, [\base, #TASK_CTX_X8]
	stp		x12, x13, [\base, #TASK_CTX_X12]
	stp		x14, x15, [\base, #TASK_CTX_X14]
	stp		x16, x17, [\base, #TASK_CTX_X16]
	stp		x18, x19, [\base, #TASK_CTX_X18]
	stp		x20, x21, [\base, #TASK_CTX_X20]
	stp		x22, x23, [\base, #TASK_CTX_X22]
	stp		x24, x25, [\base, #TASK_CTX_X24]
	stp		x26, x27, [\base, #TASK_CTX_X26]
	stp		x28, x29, [\base, #TASK_CTX_X28]
	str		x30, [\base, #TASK_CTX_LR]
.endm

.macro reg_restore base
	ldp		x30, x12, [\base, #TASK_CTX_LR]
	mov		sp, x12

	ldp		x0, x1, [\base, #TASK_CTX_X0]
	ldp		x2, x3, [\base, #TASK_CTX_X2]
	ldp		x4, x5, [\base, #TASK_CTX_X4]
	ldp		x6, x7, [\base, #TASK_CTX_X6]
	ldp		x8, x9, [\base, #TASK_CTX_X8]
	ldp		x12, x13, [\base, #TASK_CTX_X12]
	ldp		x14, x15, [\base, #TASK_CTX_X14]
	ldp		x16, x17, [\base, #TASK_CTX_X16]
	ldp		x18, x19, [\base, #TASK_CTX_X18]
	ldp		x20, x21, [\base, #TASK_CTX_X20]
	ldp		x22, x23, [\base, #TASK_CTX_X22]
	ldp		x24, x25, [\base, #TASK_CTX_X24]
	ldp		x26, x27, [\base, #TASK_CTX_X26]
	ldp		x28, x29, [\base, #TASK_CTX_X28]
	ldp		x10, x11, [\base, #TASK_CTX_X10]
.endm

.macro trap_handler el:req, ht:req, regsize:req, label:req
	.text
	.align 3
el\el\ht\()_\regsize\()_\label:
	/* preserve space to backup context registers */
	sub		sp, sp, #CTX_REG_SZ

	/* backup x10, x11 first before using them */
	/* TODO: should check if stack overflow happened */
	stp		x10, x11, [sp, #-32]!

	/* load stack address offset to save the context */
	mov		x10, sp
	add		x10, x10, #32
	reg_backup	x10

	/* load original x10, x11 and backup them */
	ldp		x12, x13, [sp], #32
	stp		x12, x13, [x10, #TASK_CTX_X10]
	mov		x12, sp
	str		x12, [x10, #TASK_CTX_SP]

	/*
	 * call to trap handler in C environment
	 * The handler itself should update elr if needed
	*/
	bl		el\el\ht\()_\regsize\()_\label\()_handler

	/* restore context */
	mov		x10, sp
	reg_restore	x10

	/* free backup context registers space */
	add		sp, sp, #CTX_REG_SZ

	/* return to normal mode */
	eret
.endm

	.text
	.global switch_to
	.align 3
switch_to:
	/* Context switch from current to next
	   x0: previous task to backup
	   x1: next task to switch to */

	/* backup x10, x11 first before using them */
	/* TODO: should check if stack overflow happened */
	stp		x10, x11, [sp, #-32]!

	/* load offset of context to task struct */
	mov		x10, #TASK_CTX

	/* if there is no previous task, skip backup part
	   this is only happened during kernel just started */
	cmp		x0, #0
	beq		1f

	/* get previous task's context */
	add		x11, x0, x10
	reg_backup	x11

	/* load original x10, x11 and backup them */
	ldp		x12, x13, [sp], #32
	stp		x12, x13, [x11, #TASK_CTX_X10]
	mov		x12, sp
	str		x12, [x11, #TASK_CTX_SP]

1:
	add		x11, x1, x10
	reg_restore	x11

	/* jump to next task */
	ret

	trap_handler	1, h, 64, sync
	trap_handler	1, h, 64, irq
	trap_handler	1, h, 64, fiq
	trap_handler	1, h, 64, serror

hang:
	b hang

	.text
	.align 11
	.global trap_vector
trap_vector:
	/* trap from current EL with SP_EL0 */
	.align 7	/* synchronous */
	b hang
	.align 7	/* IRQ */
	b hang
	.align 7	/* FIQ */
	b hang
	.align 7	/* SError */
	b hang
	/* trap from current EL with SP_ELx */
	.align 7	/* synchronous */
	b el1h_64_sync
	.align 7	/* IRQ */
	b el1h_64_irq
	.align 7	/* FIQ */
	b el1h_64_fiq
	.align 7	/* SError */
	b el1h_64_serror
	/* trap from lower EL with AArch64 */
	.align 7	/* synchronous */
	b hang
	.align 7	/* IRQ */
	b hang
	.align 7	/* FIQ */
	b hang
	.align 7	/* SError */
	b hang
	/* trap from lower EL with AArch32 */
	.align 7	/* synchronous */
	b hang
	.align 7	/* IRQ */
	b hang
	.align 7	/* FIQ */
	b hang
	.align 7	/* SError */
	b hang

	.end
