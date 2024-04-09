#ifndef _COMPILER_H_
#define _COMPILER_H_

#ifndef offsetof
#define offsetof(type, member)		((uintptr_t)&((type *)0)->member)
#endif

#define container_of(ptr, type, member)	({				\
	const typeof(((type *)0)->member) *__mptr = (ptr);		\
	(type *)((char *)__mptr - offsetof(type, member));		\
	})

#endif /* _COMPILER_H_ */
