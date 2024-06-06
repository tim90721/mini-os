#ifndef _RISC_V_
#define _RISC_V_

#include <types.h>

static inline void set_mtvec(void (*handler)(void))
{
	__asm__ __volatile__("csrw mtvec, %0" : : "r"(handler));
}
#endif /* _RISC_V_ */
