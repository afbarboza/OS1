#include "list.h"
#include <stdlib.h>
#include <stdio.h>

struct list *list_create(void)
{
	struct list *_list = NULL;
	struct node *_head = NULL;
	struct node *_tail = NULL;
	
	_head = (struct node *) malloc(sizeof(struct node));
	_tail = (struct node *) malloc(sizeof(struct node));
	_list = (struct list *) malloc(sizeof(struct list));

	if (!_head || !_tail || !_list) {
		return NULL;
	}

	/*head and tail _does not_ store data at all*/
	_head->item = NULL;
	_tail->item = NULL;

	_head->next = _tail;
	_tail->next = NULL;

	_head->prev = NULL;
	_tail->prev = _head;

	_list->head = _head;
	_list->tail = _tail;
	return _list;
}

void    list_destroy(struct list *l)
{
	struct node *tmp = NULL;

	if (!l) {
		fprintf(stderr, "list.c:34: null pointer passed as parameter.\n");
		return;
	}

	while (l->head != NULL) {
		tmp = l->head;
		l->head = l->head->next;
		free(tmp);
	}

	free(l);
}

inline uint8_t list_empty(struct list *l)
{
	if (!l) {
		fprintf(stderr, "list.c:52: null pointer passed as parameter");
	}

	return ((l->head->next == l->tail && l->tail->prev == l->head));
}

uint8_t list_add_tail(struct list *l, void *item)
{
	struct node *prev_tail = NULL, *n = NULL;

	if (!l || !item) {
		fprintf(stderr, "list.c:52: null pointer passed as parameter.\n");
		return 0;
	}

	n = (struct node *) malloc(sizeof(struct node));
	if (!n) {
		fprintf(stderr, "list.c:70: not enough memory.\n");
		exit(1);
	}

	n->item = item;
	n->next = NULL;
	n->prev = NULL;

	prev_tail = l->tail->prev;
	/*setting new node pointers*/
	n->next = l->tail;
	n->prev = prev_tail;
	/*fixing list pointers*/
	l->tail->prev = n;
	prev_tail->next = n;
	return 1;
}

uint8_t list_add_head(struct list *l, void *item)
{
	struct node *next_head = NULL, *n = NULL;
	if (!l || !item) {
		fprintf(stderr, "list.c:66: null pointer passed as parameter.\n");
		return 0;
	}

	n = (struct node *) malloc(sizeof(struct node));
	if (!n) {
		fprintf(stderr, "list.c:98: not enough memory.\n");
		exit(1);
	}

	n->item = item;
	n->prev = NULL;
	n->next = NULL;

	next_head = l->head->next;
	/*setting new node pointers*/
	n->next = next_head;
	n->prev = l->head;
	/*fixing list pointers*/
	l->head->next = n;
	next_head->prev = n;
	return 1;
}

void *list_del_tail(struct list *l)
{
	struct node *tail_prev = NULL;
	if (!l) {
		fprintf(stderr, "list.c:80: null pointer passed as parameter.\n");
		return NULL;
	}

	if (list_empty(l)) {
		return NULL;
	}

	tail_prev = l->tail->prev; /*marking the element to be removed*/
	/*fixing prev pointer of tail*/
	l->tail->prev = tail_prev->prev;
	/*fixing pointer to tail node*/
	tail_prev->prev->next = l->tail;
	/*cleaning fields*/
	void *retval = tail_prev->item;
	tail_prev->prev = NULL;
	tail_prev->next = NULL;
	free(tail_prev);
	return retval;
}

void *list_del_head(struct list *l)
{
	struct node *next_head = NULL;

	if (!l) {
		fprintf(stderr, "list.c:108: null pointer passed as parameter.\n");
		return NULL;
	}
	
	if (list_empty(l)) {
		return NULL;
	}

	next_head = l->head->next;	/*marking the element to be removed*/
	/*fixing next pointer of head*/
	l->head->next = next_head->next;
	/*fixing pointer to head node*/
	next_head->next->prev = l->head;
	/*cleaning fields*/
	void *retval = next_head->item;
	next_head->prev = NULL;
	next_head->next = NULL;
	free(next_head);
	return retval;
}
