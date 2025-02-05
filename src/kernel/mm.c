#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include <align.h>

#include <mm/mm.h>

extern char __bss_start[];
extern char __bss_end[];
extern char __heap_start[];
extern char __heap_size[];

struct mm_core {
	struct list_node free_list;
	struct list_node alloc_list;
	addr_t heap_start;
	addr_t heap_end;
	u32 heap_size;
	u32 page_cnt;
};

struct mm_core mcore;

static void ___free_page(struct mm_struct *mm)
{
	u32 cnt = mm->len / PAGE_SIZE;
	struct mm_struct *next;

	for (next = list_next_entry(mm, node);
	     cnt;
	     cnt--, mm = next, next = list_next_entry(mm, node)) {
		list_del(&mm->node);
		list_add_tail(&mm->node, &mcore.free_list);
		mm->len = PAGE_SIZE;
	}
}

static void __free_page(addr_t base)
{
	struct mm_struct *mm;
	bool found = false;

	/* perform an O(n) algorithm to find the start of the page entry */
	list_for_each_entry(mm, &mcore.alloc_list, node) {
		if (mm->base == base) {
			found = true;
			break;
		}
	}

	if (!found)
		return;

	/* free one page */
	if (mm->len == PAGE_SIZE) {
		list_del(&mm->node);
		list_add_tail(&mm->node, &mcore.free_list);
		return;
	}

	/* otherwise free multiple page */
	___free_page(mm);
}

/*
 * use a rather stupid method right now since it is not expected to free
 * page in this development stage
 * TODO: enable virtual memory before we do actual memory management
 */
void free_page(void *addr)
{
	addr_t base = (addr_t)addr;

	if (!base)
		return;

	/* check the page is aligned */
	if (base & (PAGE_SIZE - 1))
		return;

	/* check the page is in reasonable range */
	if (base < mcore.heap_start || base > mcore.heap_end)
		return;

	__free_page(base);
}

static void *alloc_one_page(void)
{
	struct mm_struct *mm;

	mm = list_first_entry(&mcore.free_list, struct mm_struct, node);

	list_del(&mm->node);
	list_add_tail(&mm->node, &mcore.alloc_list);

	mm->len = PAGE_SIZE;

	return (void *)mm->base;
}

static void *__alloc_page(u32 cnt)
{
	struct mm_struct *head;
	struct mm_struct *next;
	struct mm_struct *mm;
	addr_t prev_base = 0;
	u32 num = 0;

	/* find continuous region that fits the requirement */
	list_for_each_entry(mm, &mcore.free_list, node) {
		if (prev_base + PAGE_SIZE == mm->base) {
			if (++num == cnt)
				break;
		} else {
			head = mm;
			num = 1;
		}
		prev_base = mm->base;
	}

	/* return if no continuous space */
	if (num != cnt)
		return NULL;

	/* preserve head->next and move head from free list */
	next = list_next_entry(head, node);
	list_del(&head->node);
	num--;

	while (num--) {
		mm = next;
		mm->len = 0;
		next = list_next_entry(mm, node);

		list_del(&mm->node);
		list_add_tail(&mm->node, &head->node);
	}

	/* update page size */
	head->len = PAGE_SIZE * cnt;

	/* join allocated new list to allocated list */
	list_join(&head->node, &mcore.alloc_list);

	return (void *)head->base;
}

void *alloc_page(u32 cnt)
{
	if (cnt == 0 || list_empty(&mcore.free_list))
		return NULL;

	if (cnt == 1)
		return alloc_one_page();

	return __alloc_page(cnt);
}

static void memory_list_init(struct mm_struct *mm_base)
{
	struct mm_struct *mm;
	u32 i;

	/* initialize memory head */
	list_node_init(&mcore.free_list);
	list_node_init(&mcore.alloc_list);

	/* initialize all mm struct */
	for (i = 0; i < mcore.page_cnt; i++) {
		mm = &(mm_base[i]);

		/* assign base address */
		mm->base = mcore.heap_start + PAGE_SIZE * i;
		mm->len = PAGE_SIZE;

		/* append node to free list tail */
		list_node_init(&mm->node);
		list_add_tail(&mm->node, &mcore.free_list);
	}
}

int memory_init(void)
{
	u32 page_cnt;
	u32 mgmt_page_cnt;
	addr_t heap_start_org;

	/* initialize heap end to memory end */
	mcore.heap_end = (addr_t)__heap_start + (size_t)__heap_size;
	/* align heap end 4K down */
	mcore.heap_end = ALIGN_DOWN(mcore.heap_end, PAGE_SIZE);
	/* initialize heap start and align to 4K */
	heap_start_org = ALIGN((addr_t)__heap_start, PAGE_SIZE);
	/* calculate heap size for all available heap space */
	mcore.heap_size = mcore.heap_end - heap_start_org;

	/* calculate available page count */
	page_cnt = mcore.heap_size / PAGE_SIZE;
	/* calculate number of page needed for page management */
	mgmt_page_cnt = (page_cnt * sizeof(struct mm_struct)) / PAGE_SIZE + 1;
	/* reserve page entry management memory */
	mcore.page_cnt = page_cnt - mgmt_page_cnt;
	mcore.heap_start = heap_start_org + mgmt_page_cnt * PAGE_SIZE;
	/* calculate heap size except memory management space */
	mcore.heap_size = mcore.heap_end - mcore.heap_start;

	memory_list_init((struct mm_struct *)heap_start_org);

#if CONFIG_DEBUG_TRACE
	printf("heap start: %x, heap end: %x, heap size: %x\n",
		mcore.heap_start, mcore.heap_end, mcore.heap_size);
	printf("org page cnt: %d, mgmt page cnt: %d, available page cnt: %d\n",
		page_cnt, mgmt_page_cnt, mcore.page_cnt);
#endif /* CONFIG_DEBUG_TRACE */

	return 0;
}
