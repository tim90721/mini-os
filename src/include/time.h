#ifndef _TIME_H_
#define _TIME_H_

#include <stdint.h>

extern size_t tick;

int arch_time_init(void);
int time_init(void);
#endif /* _TIME_H_ */
