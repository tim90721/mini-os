#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <trap.h>

#include <arch/riscv.h>

/* define in entry.S */
extern void riscv_trap_vector(void);

int trap_init(void)
{
	/*
	 * initialize trap assembly handler,
	 * eventually it will call to riscv_trap_handler()
	 */
	set_mtvec(riscv_trap_vector);

	return 0;
}

reg_t riscv_trap_handler(reg_t mepc, reg_t mcause)
{
	if (mcause & MCAUSE_IRQ) {
		printf("IRQ handler not implement yet");
	} else {
		printf("mcause: %u\n", mcause);
		exit(-EINVAL);
	}

	return mepc;
}
