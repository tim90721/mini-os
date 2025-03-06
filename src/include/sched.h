#ifndef _SCHED_H_
#define _SCHED_H_

#include <stdbool.h>
#include <stddef.h>

#include <task.h>

extern struct task_struct *current;

extern void switch_to(struct task_struct *prev, struct task_struct *next);

bool sched_has_task_woken(void);
void sched_check_tick(void);
void schedule(void);
int sched_init(void);
#endif /* _SCHED_H_ */
