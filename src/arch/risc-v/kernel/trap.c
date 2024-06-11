#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <interrupt.h>

#include <arch/riscv.h>
#include <arch/trap.h>

/* define in entry.S */
extern void riscv_trap_vector(void);

int trap_init(void)
{
	/*
	 * initialize trap assembly handler,
	 * eventually it will call to riscv_trap_handler()
	 */
	mtvec_write(riscv_trap_vector);

	/* enable current hart's MIE machine mode external interrupt */
	mie_write(mie_read() | MIE_MEIE);

	/* enable current hart's MSTATUS interrupt */
	mstatus_write(mstatus_read() | MSTATUS_MIE);

	return 0;
}

reg_t riscv_trap_handler(reg_t mepc, reg_t mcause)
{
	if (mcause & MCAUSE_IRQ) {
		if (!arch_irq_handler)
			exit(-ENODEV);

		arch_irq_handler();
	} else {
		exit(-EINVAL);
	}

	return mepc;
}
