#include "defs.h"
#include "list.h"
#include "busstop.h"

#include <stdio.h>
#include <stdlib.h>

/*TODO: erase documentation from .c files*/

/**
*	init_stopbus - main function of thread stopbus
*	
*	@arg - id of the executing corresponding thread
*/
void *init_busstop(void *arg)
{
	/*TODO: code here*/
	return NULL;
}

/**
*	create_busstop - allocates and initializes the struct  bustop
*
*	@bus_thread - the execution thread corresponding to the 
*			    struct.
*	
*	this function returns a pointer to an struct busstop or NULL if
*	any error occured.
*
*/
busstop_t *create_busstop(pthread_t *bus_thread, uint32_t _id_busstop)
{
	busstop_t *new_busstop = NULL;
	if (!bus_thread) {
		fprintf(stderr, "busstop.c:31: null pointer passed as parameter.\n");
		exit(1);
	}

	if (_id_busstop < 0) {
		fprintf(stderr, "busstop.c:31: negative value for _id_busstop");
		return NULL;
	}

	new_busstop = (busstop_t *) malloc(sizeof(busstop_t));
	if (!new_busstop) {
		fprintf(stderr, "busstop.c:34: not enough memory.\n");
		exit(1);
	}

	new_busstop->id_bustop = _id_busstop;
	new_busstop->critical_busy_bus = ENOSTOPBUS;
	new_busstop->passenger = ENOPASSENGER;
	new_busstop->port_status = ENODOOR;
	new_busstop->exec_busstop = bus_thread;
	new_busstop->critical_ready_passengers = list_create();
	new_busstop->critical_blocked_passengers = list_create();
	return new_busstop;
}

/**
*	empty_stopbus - checks whether a given stopbus is busy
*			   with a bus or its free to receveive a
*			   new bus
*
*	@stop: the pointer to the stopbus to be checked.
*/
inline uint8_t empty_busstop(busstop_t *stop)
{
	/*TODO: code here*/
	return 0;
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
*	
*	@_busstop - the busstop pointing to the stopped bus.
*
*	return a ppointer to the bus stopped there, or NULL otherwise.
*/
bus_t	*acquire_bus(busstop_t *_busstop)
{
	/*TODO: code here*/
	return NULL;
}

/**
*	do_departure - departures the first available passenger.
*		       i.e.: insert at stopped bus the next passenger
*/
void	do_departure(busstop_t *_busstop)
{
	/*TODO: code here*/
}

/**
*	list_ready_add - adds a @_passenger to the list_ready
*
*	this function SHALL NOT be called from other files
*/
static void 	list_ready_add(passenger_t *_passenger)
{
	/*TODO: code here*/
}

/**
*	list_blocked_add - adds a @_passenger to the list_blocked
*
*	this function SHALL NOT be called from other files
*/
static void	list_blocked_add(passenger_t *_passenger)
{
	/*TODO: code here*/
}

/**
*	list_ready_first - remove the first element of list_ready.
*	
*	return the removed element. SHALL NOT be called from other files
*/
static	passenger_t *list_ready_first(void)
{
	/*TODO: code here*/
	return NULL;
}

/**
*	list_blocked_first - remove the first element of list_blocked
*
*	return the removed element. SHALL NOT be called from other files
*/
static	passenger_t *list_blocked_first(void)
{
	return NULL;
}

/**
*	acquire_passenger - gets the arrived passenger from the bus and
*			    inserts at the end of the queue of passengers
*
*/
void	acquire_passenger(busstop_t *_busstop, passenger_t *pass)
{
}

/**
*	release_passenger - gives to the stopped bus the first available
*			    passenger.
*
*	returns the first available passenger or NULL if there is
*	no avaible passengers.
*/
passenger_t	*release_passenger(void)
{
	return NULL;
}

/**
*	self_bus - returns the corresponding struct of the
*		   executing thread.
*
*/
busstop_t	*self_bus(pthread_t *bus_thread)
{
	return NULL;
}

