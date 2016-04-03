#include <stdio.h>
#include "list.h"
#include "defs.h"
#include "passenger.h"
#include "busstop.h"
#include "bus.h"

int main(void)
{
	struct list *l = list_create();
	if (l)
		printf("hello world.\n");
	return 0;
}
