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

	.text
	.global switch_to
	.align 3
switch_to:
	/* Context switch from current to next
	   x0: previous task to backup
	   x1: next task to switch to */

	/* backup x10, x11 first before using them */
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
