#include "defs.h"
#include "list.h"
#include "busstop.h"
#include "passenger.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

/*
TODO: erase documentation from .c files
create global mutexes for empty_busstop
*/

extern uint32_t        global_bus_busstop;
extern pthread_mutex_t lock_bus_busstop;

extern uint32_t        nthreads_passengers;
extern pthread_mutex_t lock_bus;

/**
*	init_stopbus - main function of thread stopbus
*	
*	@arg - id of the executing corresponding thread
*/
void *init_busstop(void *arg)
{
	uint32_t id_stop = (uint32_t) arg;
	if (id_stop < 0) {
		fprintf(stderr, "passenger.c:20: negative value as parameter.\n");
	}

	while (!end_of_process()) {
		while (has_bus(busstop_s[i])) {
			busstop_s[i]->port_status = PORT_DOWN;
		}
	}

	return NULL;
}

/**
*	create_busstop - allocates and initializes the struct  busstop
*
*	@bus_thread - the execution thread corresponding to the 
*			    struct.
*	
*	this function returns a pointer to an struct busstop or NULL if
*	any error occured.
*
*/
busstop_t *create_busstop(pthread_t *busstop_thread, uint32_t _id_busstop)
{
	/*ponteiro de retorno*/
	busstop_t *new_busstop = NULL;

	/*verificacao de argumento*/
	if (!busstop_thread) {
		fprintf(stderr, "busstop.c:31: null pointer passed as parameter.\n");
		exit(1);
	}

	if (_id_busstop < 0) {
		fprintf(stderr, "busstop.c:31: negative value for _id_busstop");
		return NULL;
	}

	/*alocando a estrutura de retorno*/
	new_busstop = (busstop_t *) malloc(sizeof(busstop_t));

	/**/
	if (!new_busstop) {
		fprintf(stderr, "busstop.c:34: not enough memory.\n");
		exit(1);
	}

	pthread_mutex_init(&(new_busstop->lock_port), NULL);
	pthread_cond_init(&(new_busstop->cond_door), NULL);
	pthread_mutex_init(&new_busstop->lock_busy_bus, NULL);
	sem_init(&new_busstop->lock_counter_ready, 0, 1);
	sem_init(&new_busstop->list_full, 0, MAX_READY_QUEUE);
	new_busstop->id_bustop = _id_busstop;
	new_busstop->critical_busy_bus = ENOSTOPBUS;
	new_busstop->passenger = ENOPASSENGER;
	new_busstop->port_status = ENODOOR;
	new_busstop->exec_busstop = busstop_thread;
	new_busstop->critical_ready_passengers = list_create();
	new_busstop->critical_blocked_passengers = list_create();
	return new_busstop;
}

/**
*	empty_stopbus - checks whether a given stopbus is busy
*			   with a bus or its free to receveive a
*			   new bus. if so
*
*	@stop: the pointer to the stopbus to be checked.
*/
inline uint8_t empty_busstop(busstop_t *stop, bus_t *_bus)
{
	int retval = 0;
	CHECK_NULL(stop, "busstop.c:84: ");
	CHECK_NULL(_bus, "busstop.c:84: ");

	pthread_mutex_lock(&(stop->lock_busy_bus));
	if (stop->critical_busy_bus == ENOSTOPBUS) {
		stop->critical_busy_bus = _bus;
		_bus->critical_stopped = stop;
		retval = 1;
	} else {
		retval = 0;
	}
	pthread_mutex_unlock(&(stop->lock_busy_bus));
	return retval;
}

inline uint8_t has_bus(busstop_t *stop)
{
	CHECK_NULL(stop, "busstop.c:117 ");
	int retval = 0;
	pthread_mutex_lock(&(stop->lock_busy_bus));
	if (stop->critical_busy_bus == ENOSTOPBUS) {
		retval = 1;
	} else {
		retval = 0;
	}
	pthread_mutex_unlock(&(stop->lock_busy_bus));
	return retval;
}


/**
*	busstop_destroy - destroys the given busstop and then  
*			  exits the corresponding thread.
*			  
*	@busstop: the busstop to be destroyed
*/
void 	busstop_destroy(busstop_t *busstop)
{
	/*TODO: code here*/
}

/**
*	acquire_bus - try to return the stopped bus at a given busstop
*		      for a given @pass passenger.
*	
*	@_busstop - the busstop pointing to the stopped bus.
*	@pass - the passenger asking for the bus.
*
*
*	NOTES:
*		this function SHALL NOT BE USED excepet for passengers threads.
*		this function only returns NON NULL if, and only if:
*		a) the @pass is the first of the queue.
*		b) there is a bus stoped there and
*		c) the port status is PORT_UP
*		OTHERWISE, this function must fails and return NULL
*	return a ppointer to the bus stopped there, or NULL otherwise.
*/
bus_t	*acquire_bus(busstop_t *_busstop, passenger_t *pass, uint8_t new_status)
{
	CHECK_NULL(_busstop, "busstop.c:161");
	CHECK_NULL(pass, "busstop.c:161");
	passenger_t *first_ptr = NULL;
	bus_t *retval = NULL;

	if (!list_empty(_busstop->critical_ready_passengers))
		first_ptr = _busstop->critical_ready_passengers->head->next;

	if (first_ptr != pass || first_ptr == NULL)
		return retval;

	pthread_mutex_lock(&(_busstop->lock_port));
	if (_busstop->port_status == PORT_UP) {
		pass->status = new_status;
		pthread_cond_signal(&(pass->cond_pass_status), 
				    &(pass->lock_pass_status));
		retval = _busstop->critical_busy_bus;
	}
	pthread_mutex_unlock(&(_busstop->lock_port));
	return _busstop->critical_busy_bus;
}

/**
*	do_departure - departures the first available passenger.
*		       i.e.: insert at stopped bus the next passenger
*/
passenger_t	do_departure(busstop_t *_busstop)
{
	CHECK_NULL(_busstop, "busstop.c:161: ");
	
}

/**
*	list_ready_add - adds a @_passenger to the list_ready
*
*	this function SHALL NOT be called from other files
*/
static void 	list_ready_add(busstop_t *_stop, passenger_t *_passenger)
{
	if (!_stop || !_passenger) {
		fprintf(stderr, "busstop.c:113: null pointer passed as parameter.\n");
		exit(1);
	}

	list_add_tail(_stop->critical_ready_passengers, _passenger);
}

/**
*	list_blocked_add - adds a @_passenger to the list_blocked
*
*	this function SHALL NOT be called from other files
*/
static void	list_blocked_add(busstop_t *_stop, passenger_t *_passenger)
{
	if (!_stop || !_passenger) {
		fprintf(stderr, "busstop.c:128: null pointer passed as parameter.\n");
		exit(1);
	}

	list_add_tail(_stop->critical_blocked_passengers, _passenger);
}

/**
*	list_ready_first - remove the first element of list_ready from @_stop
*	
*	return the removed element. SHALL NOT be called from other files
*/
static	passenger_t *list_ready_first(busstop_t *_stop)
{
	if (!_stop) {
		fprintf(stderr, "busstop.c:143: null pointer passed as parameter.\n");
		exit(1);
	}
	return list_del_head(_stop->critical_ready_passengers);
}

/**
*	list_blocked_first - remove the first element of list_blocked
*
*	return the removed element. SHALL NOT be called from other files
*/
static	passenger_t *list_blocked_first(busstop_t *_stop)
{
	if (!_stop) {
		fprintf(stderr, "busstop.c:143: null pointer passed as parameter.\n");
		exit(1);
	}
	return list_del_head(_stop->critical_blocked_passengers);
}

/**
*	acquire_passenger - gets the arrived passenger from the bus and
*			    inserts at the end of the queue of passengers
*
*/
void	acquire_passenger(busstop_t *_busstop, 
			  passenger_t *pass, 
			  uint8_t status_flag)
{
	CHECK_NULL(_busstop, "busstop.c:208 ");
	CHECK_NULL(pass, "busstop.c:208 ");

	/*race conditions*/
	sem_wait(&(_busstop->list_full));
	sem_wait(&(_busstop->lock_queue));
	/*step 1: checks whether the list of ready is empty*/
	list_add_tail(_busstop->critical_ready_passengers, pass);
	pass->status = status_flag;
	sem_post(&(_busstop->lock_queue));
}

/**
*	release_passenger - gives to the stopped bus the first available
*			    passenger.
*
*	returns the first available passenger or NULL if there is
*	no avaible passengers.
*/
passenger_t	*release_passenger(busstop_t *_busstop, uint8_t status_flag)
{
	passenger_t *retval = NULL;
	CHECK_NULL(_busstop, "busstop.c:232 ");
	sem_post(&(_busstop->list_full));
	sem_wait(&(_busstop->lock_queue));
	retval = list_del_head(_busstop->critical_ready_passengers);
	if (retval == NULL) {	/*the list may be null*/
		sem_post(&(_busstop->lock_queue));
		return NULL;
	} else {
		retval->status = status_flag;
		sem_post(&(_busstop->lock_queue));
		return retval;
	}
}

/**
*	self_bus - returns the corresponding struct of the
*		   executing thread.
*
*/
busstop_t	*self_bus(pthread_t *bus_thread)
{
	if (!bus_thread) {
		fprintf(stderr, "busstop.c:192: null pointer passed as parameter.\n");
		exit(1);
	}

	return NULL;
}
