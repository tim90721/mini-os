#ifndef _LIST_H_
#define _LIST_H_

#include <compiler.h>

struct list_node {
	struct list_node *next;
	struct list_node *prev;
};

#define LIST_NODE(n)							\
	struct list_node n = { .next = &n, .prev = &n }

static inline void list_node_init(struct list_node *node)
{
	node->next = node;
	node->prev = node;
}

#define list_entry(pnode, type, member)					\
	container_of(pnode, type, member)

#define list_first_entry(pnode, type, member)				\
	container_of((pnode)->next, type, member)

#define list_last_entry(pnode, type, member)				\
	container_of((pnode)->prev, type, member)

#define list_next_entry(obj, member)					\
	list_entry((obj)->member.next, typeof(*obj), member)

#define list_prev_entry(obj, member)					\
	list_entry((obj)->member.prev, typeof(*obj), member)

#define list_empty(pnode)						\
	((pnode)->next == (pnode))

#define list_is_head(obj, head, member)					\
	(&(obj)->member == (head))

#define list_for_each_entry(obj, head, member)				\
	for ((obj) = list_first_entry((head), typeof(*obj), member);	\
	     !list_is_head(obj, head, member);				\
	     (obj) = list_next_entry(obj, member))

static inline void list_join(struct list_node *new_list, struct list_node *head)
{
	struct list_node *tail = head->prev;

	tail->next = new_list;
	head->prev = new_list->prev;
	new_list->prev->next = head;
	new_list->prev = tail;
}

static inline void list_add(struct list_node *node, struct list_node *head)
{
	node->next = head->next;
	node->prev = head;
	head->next->prev = node;
	head->next = node;
}

static inline void list_add_tail(struct list_node *node, struct list_node *head)
{
	node->next = head;
	node->prev = head->prev;
	head->prev->next = node;
	head->prev = node;
}

static inline void list_del(struct list_node *node)
{
	node->next->prev = node->prev;
	node->prev->next = node->next;

	list_node_init(node);
}
#endif /* _LIST_H_ */
