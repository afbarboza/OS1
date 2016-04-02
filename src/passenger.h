#ifndef PASSENGER_H
#define	PASSENGER_H

#define ENOATBUS	NULL
#define EATDESTINY	1
#define	EATORIGIN	1

#include <pthread.h>
#include <stdint.h>
#include <time.h>
#include "busstop.h"
#include "bus.h"

typedef struct passenger passenger_t;

/**
* 	struct passengers - all the info about the citizens who are
*		      circulating at the city.
*
*	@at_bus: pointer to bus that passenger is currently riding.
*		(ENOATBUS if passenger is not at bus).
*
*	@blocked: flag indicating whether the passenger is 
*		  sleeping at destiny.
*	@at_dest: flag indicating whteher passenger already arrived
*		  at the destiny.
*	@id_passenger: the unique identifier of passenger
*	@src:	  pointer to the source busstop.
*	@dst:	  pointer to the destiny stopbus.
*	@exec_passenger: pointer to the corresponding thread of execution
*	@sleep_time: random time used to define the amount of sleeping
*		     time.
*	@in_src_busstop: the time of arrival at origin busstop.
*	@in_src_bus:	 the time of departure time at origin busstop
*	@out_dst_bus:	 the time of arrival at destiny travel.
*	@out_src_bus:	 the time of departure time to the origin. 
*			(i.e.: the start of coming back time)
*	@out_src_bus:	the time of arrival at origin.
*/

struct passenger {
	bus_t		*at_bus;
	uint8_t		blocked;
	uint8_t		at_dst;
	uint32_t	id_passenger;
	busstop_t	*src;
	busstop_t	*dst;
	pthread_t	*exec_passenger;
	uint32_t	sleep_time;
	clock_t		in_src_busstop;
	clock_t		in_src_bus;
	clock_t		in_dst_busstop;
	clock_t		out_dst_bus;
	clock_t		out_src_bus;
}

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
