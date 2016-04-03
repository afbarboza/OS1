#ifndef LIST_H
#define LIST_H

#include <stdint.h>

struct node {
	void 		*item;
	struct node 	*next;
};

struct list {
	struct node	*head;
	struct node	*tail;
};

struct	list *list_create(void);

void	list_destroy(struct list *l);

uint8_t list_add_tail(struct list *l, struct node *n);

uint8_t list_add_head(struct list *l, struct node *n);

struct 	node *list_del_tail(struct list *l);

struct 	node *list_del_head(struct list *l);

#endif /*list.h*/
