#ifndef	BUS_H
#define BUS_H

#define	ENOSTOPBUS	NULL
#define ERDYTOGO	1
#define EFULLBUS	1
#define EFREESEAT	NULL

#include <stdint.h>
#include <pthread.h>
#include "busstop.h"
#include "passenger.h"

typedef struct bus bus_t;

/**
*	struct bus - the infos about the circulating bus at town.
*
*	@n_seats: the number of available seats when the bus is empty.
*	@id_bus:  the unique identifiqer of bus
*	@busstop: pointer to which busstop the current bus is.
*		  (or ENOSTOPBUS if not stopped at none of busstop)
*	@seats:	  pointer to the passengers who are riding at that bus.
*	@available_seats: @n_seats minus the amount of riding pasengers
*	@ready_to_go: flag indicating whhether there is no departing or
*		      arriving passengers to be done. (ERDYTOGO if so)
*	@exec_bus: pointer to the current thread of bus which is being 
*		   manipulated.	
*/
struct bus {
	uint32_t	n_seats;
	uint32_t	id_bus;
	busstop		*critical_stopped;
	passenger_t	*critical_seats;
	uint32_t	critical_available_seats;
	uint8_t		ready_to_go;
	pthread_t	*exec_bus;
};

/**
*	init_passenger - the main function of the corresponding thread
*/
void *init_passenger(void *arg);

/**
*	bus_create - allocates and initializes the struct bus
*
*	@bus_thread - the corresponding thread struct bus
*
*	this function shall return the created struct bus or NULL if any error
*	occured.
*
*/

bus_t bus_create(pthread_t *bus_thread);

/**
*
*	bus_destroy - destroys the given @_bus and exists the
*		      corresponding thread.
*/
void bus_destroy(bus_t *_bus);

/**
*	at_busstop - checks whether a given @_bus is stopped.
*	
*	returns 1 if is stopped, 0 otherwise.
*/
uint8_t at_busstop(bus_t *_bus);

/**
*	full_bus - checks wheter exists at least one available seat
*		   
*	returns 1, if the given bus is not full
*		0, otherwise.
*/
uint8_t full_bus(bus_t *_bus);

/**
*
*	receive_passenger - allocates one seat to the most recently 
*			    @passenger entered at the @_bus.
*
*	@_bus: the bus which will receive the new passenger.
*	@pass: the entered passenger.
*/
void receive_passenger(bus_t *_bus, passenger_t *pass);

/**
*
*	send_passenger: sends a passenger to the busstop which @bus is it.
*	
*/
void send_passenger(bus_t *bus);

#endif		/*bus.h*/
