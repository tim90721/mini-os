#ifndef _SCHED_H_
#define _SCHED_H_

#include <task.h>

extern struct task_struct *current;

extern void switch_to(struct context *ctx);
void schedule(void);
#endif /* _SCHED_H_ */
