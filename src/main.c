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

extern 	uint32_t        global_bus_busstop;
extern 	pthread_mutex_t lock_bus_busstop;
extern	pthread_mutex_t	lock_global_passengers;
extern	pthread_cond_t  cond_global_passengers;

extern	uint32_t        nthreads_passengers;

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

	int i = 0;
	s = atoi(argv[1]);
	c = atoi(argv[2]);
	p = atoi(argv[3]);
	a = atoi(argv[4]);

	/*initializng mutex for global counter*/
	global_bus_busstop = c;
	pthread_mutex_init(&lock_bus_busstop, NULL);

	/*counter determining the end of program*/
	nthreads_passengers = p;
	pthread_mutex_init(&lock_global_passengers, NULL);
	pthread_cond_init(&cond_global_passengers, NULL);

	/*allocating array of threads*/
	thread_bus = (pthread_t *) malloc(c * sizeof(pthread_t));
	thread_busstop = (pthread_t *) malloc(s * sizeof(pthread_t));
	thread_passengers = (pthread_t *) malloc(p * sizeof(pthread_t));

	/*allocating array of structs*/
	bus_s = (bus_t **) malloc(c * sizeof(bus_t *));
	busstop_s = (busstop_t **) malloc(s *sizeof(busstop_t *));
	passenger_s = (passenger_t **) malloc(p * sizeof(passenger_t *));


	/*creating the corresponding strucutres*/
	for (i = 0; i < c; i++) {
		bus_s[i] = bus_create(&(thread_bus[i]), i);
	}

	for (i = 0; i < s; i++) {
		busstop_s[i] = create_busstop(&(thread_busstop[i]), i);
	}

	for (i = 0; i < p; i++) {
		passenger_s[i] = passenger_create(&(thread_passengers[i]), i);
	}

	/*creating pthread busstop's*/
	for (i = 0; i < s; i++) {
		pthread_create(&(thread_busstop[i]), NULL, init_busstop, (void *) i);
	}

	for (i = 0; i < c; i++) {
		pthread_create(&(thread_bus[i]), NULL, init_bus, (void *) i);
	}

	for (i = 0; i < p; i++) {
		pthread_create(&(thread_passengers[i]), NULL, init_passenger, (void *) i);
	}

	/*TODO: print passengers trace*/

	/* main thread _must_ wait for children threads */
	for (i = 0; i < p; i++) {
		pthread_join(thread_passengers[i], NULL);
	}

	for (i = 0; i < s; i++) {
		pthread_join(thread_busstop[i], NULL);
	}

	for (i = 0; i < c; i++) {
		pthread_join(thread_bus[i], NULL);
	}

	return 0;
}
