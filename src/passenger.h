#ifndef PASSENGER_H
#define	PASSENGER_H

#define ENOATBUS	NULL
#define EATDESTINY	1
#define	EATORIGIN	1

#include <pthread.h>
#include <stdint.h>
#include <time.h>
#include "defs.h"

/**
*	init_passenger - the main function of the thread passenger.
*
*	@arg: the id of thread passenger.
*/
void *init_passenger(void *arg);

/**
*	passenger_create - allocates and initializes the passenger struct
*			  corresponding to @passenger_thread.
*	
*	@passenger_thread: the corresponding thread of to be created struct
*
*	returns a pointer to the created struct or NULL, if any error 
*		occured.
*/
passenger_t *passenger_create(pthread_t *passenger_thread);

/**
*
*	passenger_destroy - destroys the given @passenger struct and exits
*			    the corresponding thread.
*/
void passenger_destroy(passenger_t *passenger);

/**
*
*	do_arrival - takes the @pass passenger from the @_bus and then
*		     inserts into the @stop busstop.
*/
void do_arrival(passenger_t *pass, busstop_t *stop, bus_t *_bus);

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
uint8_t at_origin(passenger_t *pass, bus_t *_bus);

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
uint8_t at_destiny(passenger_t *pass, bus_t *bus);

/**
*
*	self_passenger-	gets the corresponding struct passenger of the
*			current executing thread passenger
*/
passenger_t self_passenger(pthread_t *passenger_thread);
#endif	/*passenger.h*/
