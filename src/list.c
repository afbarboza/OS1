#include "list.h"
#include <stdlib.h>

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

	_list->head = _head;
	_list->tail = _tail;
	return _list;
}
