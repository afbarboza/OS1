#ifndef	BUS_H
#define BUS_H

#define	ENOSTOPBUS	NULL
#define ERDYTOGO	1
#define EFULLBUS	1
#define EFREESEAT	NULL

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "defs.h"

/**
*	init_bus - the main function of the corresponding thread
*
*	@arg: the id of the thread bus.
*/
void *init_bus(void *arg);

/**
*	bus_create - allocates and initializes the struct bus
*
*	@bus_thread - the corresponding thread struct bus
*
*	this function shall return the created struct bus or NULL if any error
*	occured.
*
*/
bus_t *bus_create(pthread_t *bus_thread, uint32_t _id_bus);


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
*	receive_passenger - store @pas in a seat from @bus
*	@_bus: the bus which will receive the new passenger.
*	@pass: the entered passenger.
*/
void receive_passenger(bus_t *_bus, passenger_t *pass);

/**
*	send_passenger: free the seat on the @_bus that was occupied by @pass
*	@_bus: the bus which he passenger is
*	@pass: the passenger who left the bus
* Antncao adicionar o parametro passender_t *pass no cabecalho
*/
void send_passenger(bus_t *_bus);


/**
* associated_bus_busstop: checks whether _every_ bus is, initiallly, 
*			  associated with it a busstop.
* return 1, if zero.
* 	 0, otherwise
*/
inline uint8_t associated_bus_busstop(void);

/**
* down_bus_busstop - decrement the value of
*			global counter global_bus_busstop.
*/
inline void down_bus_busstop(void);

/**
* everyone gets down
*/
void arrive(bus_t *_bus);

#endif		/*bus.h*/
