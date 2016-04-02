#ifndef	STOPBUS_H
#define	STOPBUS_H

#define ENOPASSENGER	0
#define	ENODOOR		0
#define	EBUSYBYS	1

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
*	@critical_busy_bus: flag indicating whether the stopbus
*			    already is busy with a bus. _critical region_
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
	uint8_t		critical_busy_bus;
	int32_t		passenger;
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
*	non_free_stopbus - checks whether a given stopbus is busy
*			   with a bus or its free to receveive a
*			   new bus
*
*	@stop: the pointer to the stopbus to be checked.
*/
inline uint8_t empty_busstop(bustop_ *stop);

void	busstop_destroy(busstop_t *busstop);

passenger_t *acquire_passenger(void);
bus_t	*acquire_bus(void);
int	do_departure(void);
static void 	list_ready_add(passenger_t *passenger);
static void	list_blocked_add(passenger_t *passenger);
static passenger_t *list_ready_first(void);
static passenger_t *list_blocked_first(void);
void acquire_passenger(passenger_t *pass);
passenger_t release_passenger(void);
busstop_t *self_bus(pthread_t *bus_thread);
#endif	/*stopbus.h*/
