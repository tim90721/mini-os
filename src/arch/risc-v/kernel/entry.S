#include <generated/asm-offsets.h>

# explicitly not to save t6 since it is currently holding previous context
.macro reg_save base
	sw		ra, TASK_CTX_RA(\base)
	sw		sp, TASK_CTX_SP(\base)
	sw		gp, TASK_CTX_GP(\base)
	sw		tp, TASK_CTX_TP(\base)
	sw		t0, TASK_CTX_T0(\base)
	sw		t1, TASK_CTX_T1(\base)
	sw		t2, TASK_CTX_T2(\base)
	sw		s0, TASK_CTX_S0(\base)
	sw		s1, TASK_CTX_S1(\base)
	sw		a0, TASK_CTX_A0(\base)
	sw		a1, TASK_CTX_A1(\base)
	sw		a2, TASK_CTX_A2(\base)
	sw		a3, TASK_CTX_A3(\base)
	sw		a4, TASK_CTX_A4(\base)
	sw		a5, TASK_CTX_A5(\base)
	sw		a6, TASK_CTX_A6(\base)
	sw		a7, TASK_CTX_A7(\base)
	sw		s2, TASK_CTX_S2(\base)
	sw		s3, TASK_CTX_S3(\base)
	sw		s4, TASK_CTX_S4(\base)
	sw		s5, TASK_CTX_S5(\base)
	sw		s6, TASK_CTX_S6(\base)
	sw		s7, TASK_CTX_S7(\base)
	sw		s8, TASK_CTX_S8(\base)
	sw		s9, TASK_CTX_S9(\base)
	sw		s10, TASK_CTX_S10(\base)
	sw		s11, TASK_CTX_S11(\base)
	sw		t3, TASK_CTX_T3(\base)
	sw		t4, TASK_CTX_T4(\base)
	sw		t5, TASK_CTX_T5(\base)
.endm

.macro reg_restore base
	lw		ra, TASK_CTX_RA(\base)
	lw		sp, TASK_CTX_SP(\base)
	lw		gp, TASK_CTX_GP(\base)
	lw		tp, TASK_CTX_TP(\base)
	lw		t0, TASK_CTX_T0(\base)
	lw		t1, TASK_CTX_T1(\base)
	lw		t2, TASK_CTX_T2(\base)
	lw		s0, TASK_CTX_S0(\base)
	lw		s1, TASK_CTX_S1(\base)
	lw		a0, TASK_CTX_A0(\base)
	lw		a1, TASK_CTX_A1(\base)
	lw		a2, TASK_CTX_A2(\base)
	lw		a3, TASK_CTX_A3(\base)
	lw		a4, TASK_CTX_A4(\base)
	lw		a5, TASK_CTX_A5(\base)
	lw		a6, TASK_CTX_A6(\base)
	lw		a7, TASK_CTX_A7(\base)
	lw		s2, TASK_CTX_S2(\base)
	lw		s3, TASK_CTX_S3(\base)
	lw		s4, TASK_CTX_S4(\base)
	lw		s5, TASK_CTX_S5(\base)
	lw		s6, TASK_CTX_S6(\base)
	lw		s7, TASK_CTX_S7(\base)
	lw		s8, TASK_CTX_S8(\base)
	lw		s9, TASK_CTX_S9(\base)
	lw		s10, TASK_CTX_S10(\base)
	lw		s11, TASK_CTX_S11(\base)
	lw		t3, TASK_CTX_T3(\base)
	lw		t4, TASK_CTX_T4(\base)
	lw		t5, TASK_CTX_T5(\base)
	lw		t6, TASK_CTX_T6(\base)
.endm

	.text
	.global switch_to

switch_to:
	# Context switch from current to next.
	# a0: current context

	# retrieve previous context and write to t6
	csrrw		t6, mscratch, t6

	# When kernel start, current is NULL. We do not need to save context
	# at this moment.
	beqz		t6, 1f

	# save t6 previous context
	reg_save	t6

	# backup t6 previous context pointer to t5
	mv		t5, t6
	# restore original t6 from mscratch
	csrr		t6, mscratch
	# save t6 to previous context
	sw		t6, TASK_CTX_T6(t5)

1:
	# restore context to a0 (current)
	# backup a0 to t6 (last cpu register to prevent unexpected errors)
	csrw		mscratch, a0
	mv		t6, a0
	reg_restore	t6

	ret
	.end
