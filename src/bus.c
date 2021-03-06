#include "defs.h"
#include "bus.h"
#include "busstop.h"
#include "passenger.h"
#include "random.h"
#include <stdio.h>

/*guarantees that every bus has a busstop associated with it*/


extern  uint32_t       global_bus_busstop;
extern  pthread_mutex_t lock_bus_busstop;

extern  uint32_t        nthreads_passengers;
extern  pthread_mutex_t lock_global_passengers;
extern  pthread_cond_t  cond_global_passengers;

extern  uint32_t        passengers_has_busstop;
extern  pthread_mutex_t lock_passengers_busstop;
extern  pthread_cond_t  cond_passengers_busstop;

void *init_bus(void *arg)
{
	uint32_t bus_id = (uint32_t) arg;
	uint8_t has_initial_busstop = 0, not_full_bus = 0, not_empty_queue = 0;
	uint32_t random_busstop = (random_value() % s);
	passenger_t *receive_pass = NULL;	/*pass which willl be received*/
	bus_t *curr_bus = bus_s[bus_id];
	busstop_t *curr_busstop = NULL;
	sched_yield();

	/*barrier 1: wait for _all_ passengers to be created*/
	while (passengers_has_busstop != 0) {
		pthread_cond_wait(&cond_passengers_busstop, &lock_passengers_busstop);
		sched_yield();
	}
	#ifdef	DEBUG
		fprintf(stderr, "thread bus[%d]: all passengers were created.\n", bus_id);
	#endif

	/*barrier 2: wait for _all_ bus to be at a busstop*/
	while (!has_initial_busstop) {
		has_initial_busstop = empty_busstop(busstop_s[random_busstop], curr_bus);
		curr_busstop = busstop_s[random_busstop];
		random_busstop = (random_value() % s);
		#ifdef	DEBUG
			fprintf(stderr, "selecting next busstop: %d\n", random_busstop);
		#endif
		sched_yield();
	}
	down_bus_busstop();
	sched_yield();
	/*applying the same barrier to the same threads*/
	while (global_bus_busstop != 0) {
		pthread_cond_wait(&cond_bus_busstop, &lock_bus_busstop);
		sched_yield();
	}
	#ifdef	DEBUG
		fprintf(stderr, "thread bus[%d] has been allocated\n", bus_id);
	#endif

	/*ok everbody, get in. i'll take a nap while that happens*/
	while (!full_bus(curr_bus)) {
		//passenger_t *new_pass = release_passenger(curr_busstop, PASS_BUS_DST);
		//receive_passenger(curr_bus, new_pass);
		pthread_cond_wait(&(curr_bus->cond_counter_seats), 
				  &(curr_bus->lock_counter_seats));
		sched_yield();
	}
	sched_yield();

	/*thats gonna be a great day of work*/	
	has_initial_busstop = 0;
	while (!end_of_process()) {
		/*where am i gonna stop?*/
		while (!has_initial_busstop) {
			has_initial_busstop = empty_busstop(busstop_s[random_busstop], curr_bus);
			curr_busstop = busstop_s[random_busstop];
			random_busstop++;
			random_busstop = (random_busstop % s);
			sched_yield();
		}
		sched_yield();
		/*ok, finally I found a free busstop*/
		pthread_mutex_lock(&(curr_busstop->lock_port));
		/*everbody which will down -> goes down right now*/
		curr_busstop->port_status = PORT_DOWN;
		arrive(curr_bus);
		/*anybody there, wants a ride?*/
		curr_busstop->port_status = PORT_UP;
		pthread_mutex_unlock(&(curr_busstop->lock_port));
		sched_yield();
		/*everbody come in!*/
		not_full_bus = !(full_bus(curr_bus));
		not_empty_queue = has_passengers_wait(curr_busstop);
		while (not_full_bus && not_empty_queue) {
			not_full_bus = !(full_bus(curr_bus));
			not_empty_queue = has_passengers_wait(curr_busstop);
		}
		/*time for drive*/
		has_initial_busstop = 0;
		sched_yield();
	}
	pthread_cond_signal(&cond_global_passengers);
	pthread_exit(NULL);
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
	/*used to check whether a busstop already has been allocated*/
	bus_t *choosen_random = NULL;
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
	pthread_mutex_init(&(new_bus->lock_counter_seats), NULL);
	pthread_cond_init(&(new_bus->cond_counter_seats), NULL);
	new_bus->id_bus = _id_bus;
	/*a argumento de entrada da main, nro de assentos*/
	new_bus->n_seats = a;
	new_bus->critical_stopped = ENOSTOPBUS;
	new_bus->critical_available_seats = a;
	new_bus->exec_bus = bus_thread;
	new_bus->critical_seats = (passenger_t **) malloc(a * sizeof(passenger_t *));
	/*counter and mutex for how many passengers will arrive at busstop*/
	new_bus->passengers_down = 0;
	pthread_mutex_init(&(new_bus->lock_passengers_down), NULL);
	pthread_cond_init(&(new_bus->cond_passengers_down), NULL);
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
	return retval;
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
	CHECK_NULL(_bus, "bus.c:99 ");
	CHECK_NULL(pass, "bus.c:99");
	uint32_t tmp = 0;

	if (!full_bus(_bus)) {
		pthread_mutex_lock(&(_bus->lock_array_seats));
		for (tmp = 0; tmp < _bus->n_seats; tmp++) {
			/*i am so tired, thanks God I found an available seat*/
			if (_bus->critical_seats[tmp] == NULL) {
				pthread_mutex_lock(&(_bus->lock_counter_seats));
				_bus->critical_seats[tmp] = pass;
				_bus->critical_available_seats--;
				pthread_mutex_unlock(&(_bus->lock_counter_seats));
				break;
			}
		}
		pthread_mutex_unlock(&(_bus->lock_array_seats));
	}
}

/**
*	send_passenger: sends a passenger to the busstop which @bus is it.	
*/
void send_passenger(bus_t *bus)
{
}

inline uint8_t associated_bus_busstop(void)
{
	uint8_t retval = 0;
	pthread_mutex_lock(&lock_bus_busstop);
	if (global_bus_busstop == 0) {
		retval = 1;
	} else {
		retval = 0;
	}
	pthread_mutex_unlock(&lock_bus_busstop);
	return retval;
}


inline void down_bus_busstop(void)
{
	pthread_mutex_lock(&lock_bus_busstop);
	if (global_bus_busstop != 0) {
		global_bus_busstop--;
	}
	pthread_mutex_unlock(&lock_bus_busstop);
	if (global_bus_busstop == 0)
		pthread_cond_broadcast(&cond_bus_busstop);
}

void arrive(bus_t *_bus)
{
	CHECK_NULL(_bus, "bus.c:197: ");
	busstop_t *ptr_stopped = NULL;
	uint32_t i = 0, npassengers = 0;

	ptr_stopped = _bus->critical_stopped;
	if (!ptr_stopped) {
		return;
	}
	
	npassengers = _bus->n_seats;
	for (i = 0; i < npassengers; i++) {
		passenger_t *p = _bus->critical_seats[i];
		if (p != NULL) {
			uint8_t arrived = do_arrival(p, ptr_stopped, _bus);
			if (arrived) {
				pthread_mutex_lock(&(_bus->lock_array_seats));
				_bus->critical_seats[i] = NULL;
				_bus->critical_available_seats++;
				pthread_mutex_unlock(&(_bus->lock_array_seats));
			}
		}
	}
}
