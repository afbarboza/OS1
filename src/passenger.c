#include "defs.h"
#include "passenger.h"

#include <stdlib.h>

extern	uint32_t        global_bus_busstop;
extern	pthread_mutex_t lock_bus_busstop;

extern	uint32_t        nthreads_passengers;
extern	pthread_mutex_t lock_bus;

/**
*	init_passenger - the main function of the thread passenger.
*
*	@arg: the id of thread passenger.
*/
void *init_passenger(void *arg)
{
	uint32_t id_pass = (uint32_t) arg;

	while(passenger_s[id_pass]->status == PASS_BLOCKED_SRC) {
		acquire_passenger(passenger_s[id_pass]->src, passenger_s[id_pass]);
	}


	return NULL;
}

/**
*	passenger_create - allocates and initializes the passenger struct
*			  corresponding to @passenger_thread.
*	
*	@passenger_thread: the corresponding thread of to be created struct
*
*	returns a pointer to the created struct or NULL, if any error 
*		occured.
*/
passenger_t *passenger_create(pthread_t *passenger_thread, uint32_t _id_passenger)
{
	passenger_t *new_pass = NULL;
	uint32_t pass_src = 0, pass_dst = 0;
	/*checking parameters*/
	CHECK_NULL(passenger_thread, "passenger.c:23: ");

	if (_id_passenger < 0) {
		fprintf(stderr, "passenger.c:23: invalid parameter.\n");
		return NULL;
	}
	new_pass = (passenger_t *) malloc(sizeof(passenger_t));
	CHECK_MEMORY(new_pass, "passenger.c:33: ");
	/*initially, passenger is not at bus*/	
	new_pass->at_bus = ENOATBUS;
	/*setting initial status of passenger - blocked queue*/
	new_pass->status = PASS_BLOCKED_SRC;
	new_pass->id_passenger = _id_passenger;
	/*selecting, ramdomly, origin and destin*/
	new_pass->src = NULL;
	new_pass->dst = NULL;
	while (pass_src == pass_dst) {
		printf("%d %d...\n", pass_src, pass_dst);
		srand(time(NULL));
		pass_src = (uint32_t) (rand()%s);
		pass_dst = (uint32_t) (rand()%s);
	}
	new_pass->src = (busstop_s[pass_src]);
	new_pass->dst = (busstop_s[pass_dst]);
	new_pass->exec_passenger = passenger_thread;
	/*selecting sleep time at destiny - randomly*/
	srand(time(NULL));
	new_pass->sleep_time = (uint32_t) (rand()%3);
	/*pointer initialization*/
	new_pass->in_src_busstop = NULL;
	new_pass->in_src_bus = NULL;
	new_pass->in_dst_busstop = NULL;
	new_pass->out_dst_bus = NULL;
	new_pass->out_src_bus = NULL;
	time_t rawtime;
	time(&rawtime);
	new_pass->in_src_busstop = localtime(&rawtime);
	return new_pass;
}

/**
*
*	passenger_destroy - destroys the given @passenger struct and exits
*			    the corresponding thread.
*/
void passenger_destroy(passenger_t *passenger)
{
}

/**
*
*	do_arrival - takes the @pass passenger from the @_bus and then
*		     inserts into the @stop busstop.
*/
void do_arrival(passenger_t *pass, busstop_t *stop, bus_t *_bus)
{
}

/**
*	at_origin - checks whether the passenger already came back to
*		    origin place, when still is in bus.
*
*	@pass: passenger to be verified.
*	@_bus: 	the stopped bus, which will indicate the busstop where
*		passenger is at.
*
*	returns	1, if already came back to origin place.
*		0, otherwise.
*/
uint8_t at_origin(passenger_t *pass, bus_t *_bus)
{
	return 0;
}

/**
*	at_destiny - 	checks whether the passenger already arrived to
*			destiny place, when still is in bus.
*
*	@pass: 	passenger to be verified.
*	@_bus: 	the stopped bus, which will indicate the busstop where
*		passenger is at.
*
*	returns	1, if already arrived to origin place.
*		0, otherwise.
*/
uint8_t at_destiny(passenger_t *pass, bus_t *bus)
{
	CHECK_NULL(pass, "passenger.c:119: ");
	CHECK_NULL(bus, "passenger.c:119: ");
	return 0;
}

/**
*
*	self_passenger-	gets the corresponding struct passenger of the
*			current executing thread passenger
*/
passenger_t *self_passenger(pthread_t *passenger_thread)
{
	CHECK_NULL(passenger_thread, "passennger.c:129: ");
	return NULL;
}

inline uint8_t	end_of_process(void)
{
	return (nthreads_passengers == 0);
}
