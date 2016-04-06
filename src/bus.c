#include "defs.h"
#include "bus.h"
#include <stdio.h>

extern uint32_t        global_bus_busstop;
extern pthread_mutex_t lock_bus_busstop;

extern uint32_t        nthreads_passengers;
extern pthread_mutex_t lock_bus;

/**
*	init_bus - the main function of the corresponding thread
*
*	@arg: the id of the thread bus.
*/
void *init_bus(void *arg)
{
	return NULL;
}

/**
*	bus_create - allocates and initializes the struct bus
*
*	@bus_thread - the corresponding thread struct bus
*	@_id_bus - the id of bus to be created.
*
*	this function shall return the created struct bus or NULL if any error
*	occured.
*
*/

bus_t *bus_create(pthread_t *bus_thread, uint32_t _id_bus)
{
	/*the new created bus to be returned*/
	bus_t *new_bus = NULL;
	/*id of initial busstop which @bus_thread will be*/
	uint32_t random = 0;

	/*checking for incorrect parameters*/
	if (!bus_thread || _id_bus < 0) {
		fprintf(stderr, "bus.c:22: invalid parameters.\n");
		return NULL;
	}

	new_bus = (bus_t *) malloc(sizeof(bus_t));
	if (!new_bus) {
		fprintf(stderr, "bus.c:33: not enough memory.\n");
		exit(1);
	}

	/*initializes the lock of array of seats*/
	pthread_mutex_init(&(new_bus->lock_array_seats), NULL);
	/*initializes the lock of available seats*/
	pthread_mutex_init(&(new_bus->lock_counter_seats));
	new_bus->id_bus = _id_bus;
	/*a argumento de entrada da main, nro de assentos*/
	new_bus->n_seats = a;
	//new_bus->critical_stopped = ENOSTOPBUS;
	
	new_bus->critical_available_seats = a;
	new_bus->exec_bus = bus_thread;
	new_bus->critical_seats = (passenger_t **) malloc(a * sizeof(passenger_t *));
	return new_bus;
}

/**
*
*	bus_destroy - destroys the given @_bus and exists the
*		      corresponding thread.
*/
void bus_destroy(bus_t *_bus)
{
}

/**
*	at_busstop - checks whether a given @_bus is stopped.
*	
*	returns 1 if is stopped, 0 otherwise.
*/
uint8_t at_busstop(bus_t *_bus)
{
	return 0;
}

/**
*	full_bus - checks wheter exists at least one available seat
*		   
*	returns 0, if the given bus is not full
*		1, otherwise.
*/
uint8_t full_bus(bus_t *_bus)
{
	int retval = 0;
	pthread_mutex_lock(&(_bus->lock_counter_seats));
	if (_bus->critical_available_seats == 0) {
		retval = 1;
	} else {
		retval = 0;
	}
	pthread_mutex_unlock(&(_bus->lock_counter_seats));
}

/**
*
*	receive_passenger - allocates one seat to the most recently 
*			    @passenger entered at the @_bus.
*
*	@_bus: the bus which will receive the new passenger.
*	@pass: the entered passenger.
*/
void receive_passenger(bus_t *_bus, passenger_t *pass)
{
	CHECK_NULL(_buss, "bus.c:99 ");
	CHECK_NULL(pass, "bus.c:99");
	uint32_t tmp = 0;

	if (!full_bus(_bus)) {
		pthread_mutex_lock(&(_bus->lock_seats));
		for (tmp = 0; tmp < _buss->n_seats; tmp++) {
			/*i am so tired, thanks God I found an available seat*/
			if (_bus->critical_seats[i] == NULL) {
				pthread_mutex_lock(&(_bus->lock_counter_seats));
				_bus->critical_seats[i] = pass;
				_bus->critical_available_seats--;
				pthread_mutex_unlock(&(_bus->lock_counter_seats));
				break;
			}
		}
		pthread_mutex_unlock(&(_bus->lock_seats));
	}
}

/**
*	send_passenger: sends a passenger to the busstop which @bus is it.	
*/
void send_passenger(bus_t *bus)
{
}

