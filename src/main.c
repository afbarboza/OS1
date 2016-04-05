#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "list.h"
#include "defs.h"
#include "passenger.h"
#include "busstop.h"
#include "bus.h"

#define traverse_list(tmp)\
	while (tmp != NULL && tmp->item != NULL) {	\
			int value = (int) tmp->item;	\
			printf("%d\n", value);		\
			tmp = tmp->next;		\
	}

/**
* @s: numero de ponto de onibus
* @c: numero de onibus
* @p: numero de passageiros
* @a: numero de assentos
*/
int main(int argc, char *argv[])
{
	/*checando o numero de argumentos da main*/
	if (argc != 5) {
		fprintf(stderr, "main.c:16: invalid number of arguments.\n");
		exit(1);
	}

	s = atoi(argv[1]);
	c = atoi(argv[2]);
	p = atoi(argv[3]);
	a = atoi(argv[4]);

	
	thread_bus = (pthread_t *) malloc()
	return 0;
}
