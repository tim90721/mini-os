#ifndef _RISC_V_
#define _RISC_V_

#include <bits.h>
#include <stdint.h>

/* MIE */
#define MIE_SSIE		BIT(1)
#define MIE_MSIE		BIT(3)
#define MIE_STIE		BIT(5)
#define MIE_MTIE		BIT(7)
#define MIE_SEIE		BIT(9)
#define MIE_MEIE		BIT(11)

/* MSTATUS */
#define MSTATUS_MIE		BIT(3)

/* MCAUSE */
#define MCAUSE_IRQ		BIT(31)

static inline void mtvec_write(void (*handler)(void))
{
	__asm__ __volatile__("csrw mtvec, %0" : : "r"(handler));
}

static inline void mie_write(reg_t val)
{
	__asm__ __volatile__("csrw mie, %0" : : "r"(val));
}

static inline reg_t mie_read(void)
{
	reg_t val;

	__asm__ __volatile__("csrr %0, mie" : "=r"(val));

	return val;
}

static inline void mstatus_write(reg_t val)
{
	__asm__ __volatile__("csrw mstatus, %0" : : "r"(val));
}

static inline reg_t mstatus_read(void)
{
	reg_t val;

	__asm__ __volatile__("csrr %0, mstatus" : "=r"(val));

	return val;
}
#endif /* _RISC_V_ */
