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

void *init_passenger(void *arg);
bus_t bus_create(pthread_t *bus_thread);
void bus_destroy(bus_t *_bus);
uint8_t at_busstop(bus_t *_bus);
uint8_t full_bus(bus_t *_bus);
void receive_passenger(bus_t *_bus, passenger_t *pass);
void send_passenger(bus_t *bus);
#endif		/*bus.h*/
