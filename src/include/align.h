#ifndef _ALIGN_H_
#define _ALIGN_H_

#define __ALIGN(a, b)		(((a) + (b)) & ~(b))
#define ALIGN(a, b)		__ALIGN(a, (b) - 1)
#define ALIGN_DOWN(a, b)	__ALIGN((a) - ((b) - 1), (b) - 1)
#endif /* _ALIGN_H_ */
