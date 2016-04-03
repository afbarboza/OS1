#ifndef LIST_H
#define LIST_H

#include <stdint.h>

#define	for_each_node(p, l)	\
	for(p = l->head->next; p->next != l->tail; p = p->next)

struct node {
	void 		*item;
	struct node 	*next;
	struct node	*prev;
};

struct list {
	struct node	*head;
	struct node	*tail;
};

struct	list *list_create(void);

void	list_destroy(struct list *l);

inline
uint8_t list_empty(struct list *l);

uint8_t list_add_tail(struct list *l, void *item);

uint8_t list_add_head(struct list *l, void *item);

void 	*list_del_tail(struct list *l);

void	 *list_del_head(struct list *l);

#endif /*list.h*/
