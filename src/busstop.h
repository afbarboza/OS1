#ifndef	STOPBUS_H
#define	STOPBUS_H

#define ENOPASSENGER	0	/*no passenger is at bus*/
#define	ENODOOR		0	/*the busstop door is closed*/

#include <stdint.h>
#include <pthread.h>
#include "passenger.h"
#include "bus.h"
#include "list.h"

typedef struct busstop	busstop_t;

/**
*	struct busstop - stores all the busstop data.
*
*	@id_bustop: the unique id number of the bus.
*	@busy_bus: 	pointer to the stopped bus
*	@passenger:	the number of passengers at bus
*			(ENOPASSENGER if there is no passenger)
*	@port_status:	flag indicating whether the door of the
*			busstop is cllosed.
*			(ENODOOR if door is closed)
*	@exec_busstop:	the current thread that corresponds to
*			the struct busstop.
*			(ie.: the thread who owns this struct)
*	@ready_passengers: the waken up passengers who is available
*			   to go.
*	@blocked_passengers: the sleeping passengers who are
*			     "travelling" in destiny. (i.e.: blocked)
*
*/

struct busstop {
	uint32_t	id_bustop;
	bus_t		*critical_busy_bus;
	uint32_t	passenger;
	uint8_t		port_status;
	pthread_t	*exec_busstop;
	list		*critical_ready_passengers;
	list		*critical_blocked_passengers;
};

/**
*	init_stopbus - main function of thread stopbus
*	
*	@arg - id of the executing corresponding thread
*/
void *init_busstop(void *arg);

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
busstop_t *create_busstop(pthread_t *bus_thread);

/**
*	empty_stopbus - checks whether a given stopbus is busy
*			   with a bus or its free to receveive a
*			   new bus
*
*	@stop: the pointer to the stopbus to be checked.
*/
inline uint8_t empty_busstop(bustop_t *stop);

/**
*	busstop_destroy - destroys the given busstop and then  
*			  exits the corresponding thread.
*			  
*	@busstop: the busstop to be destroyed
*/
void 	busstop_destroy(busstop_t *busstop);

/**
*	acquire_bus - try to return the stopped bus at a given busstop
*	
*	@_busstop - the busstop pointing to the stopped bus.
*
*	return a ppointer to the bus stopped there, or NULL otherwise.
*/
bus_t	*acquire_bus(busstop_t *_busstop);

/**
*	do_departure - departures the first available passenger.
*		       i.e.: insert at stopped bus the next passenger
*/
void	do_departure(busstop_t *_busstop);

/**
*	list_ready_add - adds a @_passenger to the list_ready
*
*	this function SHALL NOT be called from other files
*/
static void 	list_ready_add(passenger_t *_passenger);

/**
*	list_blocked_add - adds a @_passenger to the list_blocked
*
*	this function SHALL NOT be called from other files
*/
static void	list_blocked_add(passenger_t *_passenger);

/**
*	list_ready_first - remove the first element of list_ready.
*	
*	return the removed element. SHALL NOT be called from other files
*/
static	passenger_t *list_ready_first(void);

/**
*	list_blocked_first - remove the first element of list_blocked
*
*	return the removed element. SHALL NOT be called from other files
*/
static	passenger_t *list_blocked_first(void);

/**
*	acquire_passenger - gets the arrived passenger from the bus and
*			    inserts at the end of the queue of passengers
*
*/
void	acquire_passenger(busstop_t *_busstop, passenger_t *pass);

/**
*	release_passenger - gives to the stopped bus the first available
*			    passenger.
*
*	returns the first available passenger or NULL if there is
*	no avaible passengers.
*/
passenger_t	release_passenger(void);

/**
*	self_bus - returns the corresponding struct of the
*		   executing thread.
*
*/
busstop_t	*self_bus(pthread_t *bus_thread);

#endif	/*stopbus.h*/
