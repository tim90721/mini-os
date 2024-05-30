#include <build.h>
#include <sched.h>

void asm_offsets(void)
{
	OFFSET(TASK_CTX, struct task_struct, ctx);
	OFFSET(TASK_CTX_RA, struct task_struct, ctx.ra);
	OFFSET(TASK_CTX_SP, struct task_struct, ctx.sp);
	OFFSET(TASK_CTX_GP, struct task_struct, ctx.gp);
	OFFSET(TASK_CTX_TP, struct task_struct, ctx.tp);
	OFFSET(TASK_CTX_T0, struct task_struct, ctx.t0);
	OFFSET(TASK_CTX_T1, struct task_struct, ctx.t1);
	OFFSET(TASK_CTX_T2, struct task_struct, ctx.t2);
	OFFSET(TASK_CTX_S0, struct task_struct, ctx.s0);
	OFFSET(TASK_CTX_S1, struct task_struct, ctx.s1);
	OFFSET(TASK_CTX_A0, struct task_struct, ctx.a0);
	OFFSET(TASK_CTX_A1, struct task_struct, ctx.a1);
	OFFSET(TASK_CTX_A2, struct task_struct, ctx.a2);
	OFFSET(TASK_CTX_A3, struct task_struct, ctx.a3);
	OFFSET(TASK_CTX_A4, struct task_struct, ctx.a4);
	OFFSET(TASK_CTX_A5, struct task_struct, ctx.a5);
	OFFSET(TASK_CTX_A6, struct task_struct, ctx.a6);
	OFFSET(TASK_CTX_A7, struct task_struct, ctx.a7);
	OFFSET(TASK_CTX_S2, struct task_struct, ctx.s2);
	OFFSET(TASK_CTX_S3, struct task_struct, ctx.s3);
	OFFSET(TASK_CTX_S4, struct task_struct, ctx.s4);
	OFFSET(TASK_CTX_S5, struct task_struct, ctx.s5);
	OFFSET(TASK_CTX_S6, struct task_struct, ctx.s6);
	OFFSET(TASK_CTX_S7, struct task_struct, ctx.s7);
	OFFSET(TASK_CTX_S8, struct task_struct, ctx.s8);
	OFFSET(TASK_CTX_S9, struct task_struct, ctx.s9);
	OFFSET(TASK_CTX_S10, struct task_struct, ctx.s10);
	OFFSET(TASK_CTX_S11, struct task_struct, ctx.s11);
	OFFSET(TASK_CTX_T3, struct task_struct, ctx.t3);
	OFFSET(TASK_CTX_T4, struct task_struct, ctx.t4);
	OFFSET(TASK_CTX_T5, struct task_struct, ctx.t5);
	OFFSET(TASK_CTX_T6, struct task_struct, ctx.t6);
}
