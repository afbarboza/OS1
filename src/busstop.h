#ifndef	STOPBUS_H
#define	STOPBUS_H

#include <stdint.h>
#include <pthread.h>
#include "defs.h"
#include "list.h"

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
busstop_t *create_busstop(pthread_t *busstop_thread, uint32_t _id_busstop);

/**
*	empty_stopbus - checks whether a given stopbus is busy
*			   with a bus or its free to receveive a
*			   new bus. if so, allocates the new bus
*
*	@stop: the pointer to the stopbus to be checked.
*	@_bus: pointer to the bus that are trying to stop at @stop
*/
inline uint8_t empty_busstop(busstop_t *stop, bus_t *_bus);

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
*	@pass - the passenger ordering the bus
*	@new_status - the new new status of @pass 
*       NOTES:
*               this function SHALL NOT BE USED excepet for passengers threads.
*               this function only returns NULL if, and only if:
*               a) the @pass is the first of the queue.
*               b) there is a bus stoped there and
*               c) the port status is PORT_UP
*               OTHERWISE, this function must fails and return NULL
*       return a ppointer to the bus stopped there, or NULL otherwise.

*	return a ppointer to the bus stopped there, or NULL otherwise.
*/
bus_t   *acquire_bus(busstop_t *_busstop, passenger_t *pass, uint8_t new_status);

/**
*	do_departure - departures the first available passenger.
*		       i.e.: insert at stopped bus the next passenger
*/
void	do_departure(busstop_t *_busstop);

/**
*	list_ready_add - adds a @_passenger to the list_ready of @_stop
*
*	this function SHALL NOT be called from other files
*/
static void     list_ready_add(busstop_t *_stop, passenger_t *_passenger);

/**
*	list_blocked_add - adds a @_passenger to the list_blocked of @_stop
*
*	this function SHALL NOT be called from other files
*/
static void	list_blocked_add(busstop_t *_stop, passenger_t *_passenger);

/**
*	list_ready_first - remove the first element of list_ready from @_stop
*	
*	return the removed element. SHALL NOT be called from other files
*/
static  passenger_t *list_ready_first(busstop_t *_stop);
/**
*	list_blocked_first - remove the first element of list_blocked from @_stop
*
*	return the removed element. SHALL NOT be called from other files
*/
static  passenger_t *list_blocked_first(busstop_t *_stop);
/**
*	acquire_passenger - gets the arrived passenger @pass bus and
*			    inserts at the end of the queue of passengers of @_busstop
*	this function its also may be used for initializes the busstop queue
*
*	@_busstop - the busstop where passenger will wait at queue
*	@pass - the passenger to be inserted at wait queue of busstop
*	@status_flag - indiciates whether passenger will wait
*			PASS_WAIT_SRC or PASS_WAIT_DST
*/
void	acquire_passenger(busstop_t *_busstop, passenger_t *pass, uint8_t status_flag);

/**
*	release_passenger - gives to the stopped bus the first available
*			    passenger.
*
*	returns the first available passenger or NULL if there is
*	no avaible passengers.
*/
passenger_t     *release_passenger(busstop_t *_busstop, uint8_t status_flag);

/**
*	self_bus - returns the corresponding struct of the
*		   executing thread.
*
*/
busstop_t	*self_bus(pthread_t *bus_thread);



 /**
 *       has_bus - checks whether @stop busstop already
 *       has a bus stopped.
 *       returns 0, if no.
 *               1, otherwise
 */

inline uint8_t has_bus(busstop_t *stop);

/**
* checks whether a busstop  @stop has passenger or its empty.
* returns 1, if it has.
*	  0, otherwise
*/
uint8_t has_passengers_wait(busstop_t *stop);

#endif	/*stopbus.h*/
