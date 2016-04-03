#include <stdio.h>
#include "list.h"
#include "defs.h"
#include "passenger.h"
#include "busstop.h"
#include "bus.h"

int main(void)
{

	/*list tests*/

	struct list *l = list_create();
	if (l)
		printf("list created.\n");


	int i = 0;
	for (i = 1; i < 10; i++) {
		list_add_head(l, (void *) i);
	}

	for (i = 10; i < 20; i++) {
		list_add_tail(l, (void *) i);
	}


	printf("all elements inserted.\n");

	struct node *tmp = l->head->next;
	while (tmp != NULL && tmp->item != NULL) {
			int value = (int) tmp->item;
			printf("%d\n", value);
			tmp = tmp->next;
	}

	list_destroy(l);
	return 0;
}
