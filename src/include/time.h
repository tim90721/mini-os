#ifndef _TIME_H_
#define _TIME_H_

#include <stdint.h>

extern size_t tick;

void msleep(u32 ms);

int arch_time_init(void);

void time_tick(void);
int time_init(void);
#endif /* _TIME_H_ */
