#ifndef _SCHED_H_
#define _SCHED_H_

#include <task.h>

extern struct task_struct *current;

extern void switch_to(struct task_struct *prev, struct task_struct *next);
void schedule(void);
#endif /* _SCHED_H_ */
