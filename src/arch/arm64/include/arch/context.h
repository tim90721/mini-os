#ifndef _ARCH_CONTEXT_H_
#define _ARCH_CONTEXT_H_

#include <stdint.h>

struct context {
	reg_t x0;
	reg_t x1;
	reg_t x2;
	reg_t x3;
	reg_t x4;
	reg_t x5;
	reg_t x6;
	reg_t x7;
	/* XR */
	reg_t x8;
	/* corruptible registers, caller-saved */
	reg_t x9;
	reg_t x10;
	reg_t x11;
	reg_t x12;
	reg_t x13;
	reg_t x14;
	reg_t x15;
	/* IP0 */
	reg_t x16;
	/* IP1 */
	reg_t x17;
	/* PR */
	reg_t x18;
	/* callee saved registers */
	reg_t x19;
	reg_t x20;
	reg_t x21;
	reg_t x22;
	reg_t x23;
	reg_t x24;
	reg_t x25;
	reg_t x26;
	reg_t x27;
	reg_t x28;
	reg_t fp; /* fp */
	reg_t lr; /* lr */
	reg_t sp;
	reg_t pc;
};
#endif /* _ARCH_CONTEXT_H_ */
