#ifndef LIST_H
#define LIST_H

struct element {
	void 		*item;
	struct element 	*next;
};

struct list {
	element	*head;
	element	*tail;
};

int list_add_tail(list *l, element *e);

int list_del_tail(list *l);

int list_add_head(list *l, element *e);

int list_del_head(list *l, element *e);

struct element *list_search(void *item);

#endif /*list.h*/
