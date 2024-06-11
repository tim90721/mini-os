#ifndef _TRAP_RISC_V_H_
#define _TRAP_RISC_V_H_

#include <bits.h>
#include <types.h>

enum interrupt_id {
	SUPERVISOR_SW_IRQ = 1,
	MACHINE_SW_IRQ = 3,
	SUPERVISOR_TIMER_IRQ = 5,
	MACHINE_TIMER_IRQ = 7,
	SUPERVISOR_EXT_IRQ = 9,
	MACHINE_EXT_IRQ = 11,
	__INTERRUPT_ID_MAX,
};

enum exception_id {
	INST_ADDR_MISALIGNED = 0,
	INST_ACCESS_FAULT,
	ILLEGAL_INST,
	BREAKPOINT,
	LOAD_ADDR_MISALIGNED,
	LOAD_ACCESS_FAULT = 5,
	STORE_ADDR_MISALIGNED,
	STORE_ACCESS_FAULT,
	USER_ENV_CALL,
	SUPERVISOR_ENV_CALL,
	MACHINE_ENV_CALL = 11,
	INST_PAGE_FAULT,
	LOAD_PAGE_FAULT,
	STORE_PAGE_FAULT = 15,
	__EXCEPTION_ID_MAX,
};

int trap_init(void);
reg_t riscv_trap_handler(reg_t mepc, reg_t mcause);
#endif /* _TRAP_RISC_V_H_ */
