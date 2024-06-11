#ifndef _RISC_V_
#define _RISC_V_

#include <bits.h>
#include <types.h>

/* MCAUSE */
#define MCAUSE_IRQ		BIT(31)

static inline void set_mtvec(void (*handler)(void))
{
	__asm__ __volatile__("csrw mtvec, %0" : : "r"(handler));
}
#endif /* _RISC_V_ */
