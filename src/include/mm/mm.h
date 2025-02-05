#ifndef _MM_H_
#define _MM_H_

#include <stdint.h>

#include <list.h>

#define PAGE_SIZE		0x1000 /* 4K */

struct mm_struct {
	struct list_node node;
	addr_t base;
	size_t len;
};

void free_page(void *addr);
void *alloc_page(u32 cnt);
int memory_init(void);
#endif /* _MM_H_ */
