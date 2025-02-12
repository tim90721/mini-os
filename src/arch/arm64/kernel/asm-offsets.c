#include <build.h>
#include <sched.h>

void asm_offsets(void)
{
	OFFSET(TASK_CTX, struct task_struct, ctx);
	OFFSET(TASK_CTX_X0, struct task_struct, ctx.x0);
	OFFSET(TASK_CTX_X1, struct task_struct, ctx.x1);
	OFFSET(TASK_CTX_X2, struct task_struct, ctx.x2);
	OFFSET(TASK_CTX_X3, struct task_struct, ctx.x3);
	OFFSET(TASK_CTX_X4, struct task_struct, ctx.x4);
	OFFSET(TASK_CTX_X5, struct task_struct, ctx.x5);
	OFFSET(TASK_CTX_X6, struct task_struct, ctx.x6);
	OFFSET(TASK_CTX_X7, struct task_struct, ctx.x7);
	OFFSET(TASK_CTX_X8, struct task_struct, ctx.x8);
	OFFSET(TASK_CTX_X9, struct task_struct, ctx.x9);
	OFFSET(TASK_CTX_X10, struct task_struct, ctx.x10);
	OFFSET(TASK_CTX_X11, struct task_struct, ctx.x11);
	OFFSET(TASK_CTX_X12, struct task_struct, ctx.x12);
	OFFSET(TASK_CTX_X13, struct task_struct, ctx.x13);
	OFFSET(TASK_CTX_X14, struct task_struct, ctx.x14);
	OFFSET(TASK_CTX_X15, struct task_struct, ctx.x15);
	OFFSET(TASK_CTX_X16, struct task_struct, ctx.x16);
	OFFSET(TASK_CTX_X17, struct task_struct, ctx.x17);
	OFFSET(TASK_CTX_X18, struct task_struct, ctx.x18);
	OFFSET(TASK_CTX_X19, struct task_struct, ctx.x19);
	OFFSET(TASK_CTX_X20, struct task_struct, ctx.x20);
	OFFSET(TASK_CTX_X21, struct task_struct, ctx.x21);
	OFFSET(TASK_CTX_X22, struct task_struct, ctx.x22);
	OFFSET(TASK_CTX_X23, struct task_struct, ctx.x23);
	OFFSET(TASK_CTX_X24, struct task_struct, ctx.x24);
	OFFSET(TASK_CTX_X25, struct task_struct, ctx.x25);
	OFFSET(TASK_CTX_X26, struct task_struct, ctx.x26);
	OFFSET(TASK_CTX_X27, struct task_struct, ctx.x27);
	OFFSET(TASK_CTX_X28, struct task_struct, ctx.x28);
	OFFSET(TASK_CTX_FP, struct task_struct, ctx.fp);
	OFFSET(TASK_CTX_LR, struct task_struct, ctx.lr);
	OFFSET(TASK_CTX_SP, struct task_struct, ctx.sp);
	OFFSET(TASK_CTX_PC, struct task_struct, ctx.pc);
	DEFINE(CTX_REG_SZ, sizeof(struct context));
}
