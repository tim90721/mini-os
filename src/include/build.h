#ifndef _BUILD_H_
#define _BUILD_H_

#include <compiler.h>

#define DEFINE(sym, val)						\
	asm volatile("\n.ascii \"->" #sym " %0 " #val "\"" : : "i" (val))

#define OFFSET(sym, container, member)					\
	DEFINE(sym, offsetof(container, member))

#endif /* _BUILD_H_ */
