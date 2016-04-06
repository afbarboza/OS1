#ifndef DEFS_H
#define	DEFS_H

/**
*	defs.h - definicao de tipos e variaveis globais
*		 necessarias a todos os *.h e *.c
*
*/

#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sched.h>
#include <semaphore.h>
#include "list.h"

#define	ENOATBUS	NULL	/*passenger is not actually inside bus*/
#define	ENOSTOPBUS	NULL	/*no bus is stopped at that busstop*/
#define	ENOPASSENGER	0	/*no passenger is at that bus or busstop*/
#define	ENODOOR		1	/*the busstop door is closed*/


#define	CHECK_NULL(p, str)				\
	if (!p)						\
	fprintf(stderr, "%s: null pointer.\n", str);


#define	CHECK_MEMORY(p,str)					\
	if (!p)  {						\
	fprintf(stderr, "%s: not enough memory.\n", str);	\
	exit(1); }


#define	port_status()

/*
* the queue of busstop is _not_ infinite
* the max size of the queue is 40 passengers, only
*/
#define	MAX_READY_QUEUE	40

typedef struct busstop		busstop_t;
typedef struct bus 		bus_t;
typedef	struct passenger	passenger_t;

pthread_t *thread_bus;
pthread_t *thread_busstop;
pthread_t *thread_passengers;

bus_t 		**bus_s;		/*array of global structures bus*/
busstop_t 	**busstop_s;	/*array of global structures busstop*/
passenger_t 	**passenger_s;	/*array of global strucutures passengers*/

#ifndef GLOBAL_VARIABLES
#define GLOBAL_VARIABLES
/*guarantees that every bus has a busstop associated with it*/
uint32_t	global_bus_busstop;
pthread_mutex_t	lock_bus_busstop;

/*
 * global counter of _active_ passengers thread.
 * if (nthreads_passengers == 0) the entire process must exit
 */

uint32_t	nthreads_passengers;
pthread_mutex_t	lock_global_passengers;

/*why this is here????*/
pthread_mutex_t	lock_bus;
#endif

/*lock variables*/

/**
*	@s - number of busstop at application
*	@c - number of cars(bus) at application
*	@p - number of passengers
*	@a - number of total seats per bus
*/
uint32_t s, c, p, a;

/**
*       struct busstop - stores all the busstop data.
*
*       @id_bustop: the unique id number of the bus.
*       @busy_bus:      pointer to the stopped bus
*       @passenger:     the number of passengers at bus
*                       (ENOPASSENGER if there is no passenger)
*       @port_status:   flag indicating whether the door of the
*                       busstop is cllosed.
*                       (ENODOOR if door is closed)
*       @exec_busstop:  the current thread that corresponds to
*                       the struct busstop.
*                       (ie.: the thread who owns this struct)
*       @ready_passengers: the waken up passengers who is available
*                          to go.
*       @blocked_passengers: the sleeping passengers who are
*                            "travelling" in destiny. (i.e.: blocked)
*	@critical_size_ready: count the size of elements in the ready queue
*			      of busstop.
*	@lock_counter_ready: mutex for counting the number of passangers.
*	@list_full: semaphore for counting the number of passangers waiting:
*/

struct busstop {
        uint32_t        id_bustop;
        bus_t           *critical_busy_bus;
	pthread_mutex_t	lock_busy_bus;
        uint32_t        passenger;
        uint8_t         port_status;
	pthread_mutex_t	lock_port;
	pthread_cond_t	cond_door;
        pthread_t       *exec_busstop;
        struct list     *critical_ready_passengers;
	uint32_t	critical_size_ready;
	sem_t		lock_queue;		/*pseudo-mutex*/	
	sem_t		list_full;		/*semaphore*/
        struct list     *critical_blocked_passengers;
	bus_t		
};

/**
*       struct bus - the infos about the circulating bus at town.
*
*       @n_seats: the number of available seats when the bus is empty.
*       @id_bus:  the unique identifiqer of bus
*       @critical_stopped: pointer to which busstop the current bus is.
*                 (or ENOSTOPBUS if not stopped at none of busstop)
*       @seats:   pointer to the passengers who are riding at that bus.
*       @available_seats: @n_seats minus the amount of riding pasengers
*       @ready_to_go: flag indicating whhether there is no departing or
*                     arriving passengers to be done. (ERDYTOGO if so)
*       @exec_bus: pointer to the current thread of bus which is being 
*                  manipulated.
*	@lock_array_seats: lock the array of passengers on board. 
*	@lock_counter_seats: lock the @critical_available_seats field
*/
struct bus {
        uint32_t        n_seats;
        uint32_t        id_bus;
        busstop_t       *critical_stopped;
        passenger_t     **critical_seats;
        uint32_t        critical_available_seats;
        //uint8_t         ready_to_go;
        pthread_t       *exec_bus;
	pthread_mutex_t	lock_array_seats;
	pthread_mutex_t	lock_counter_seats;
};

/**
*       struct passengers - all the info about the citizens who are
*                     circulating at the city.
*
*       @at_bus: pointer to bus that passenger is currently riding.
*               (ENOATBUS if passenger is not at bus).
*	@status: state of thread passenger in the process
*	@lock_pass_status: mutex for checking the machine state status of thred
*	@cond_pass_status: condition variable for @lock_pass_status
*       @id_passenger: the unique identifier of passenger
*       @src:     pointer to the source busstop.
*       @dst:     pointer to the destiny stopbus.
*       @exec_passenger: pointer to the corresponding thread of execution
*       @sleep_time: random time used to define the amount of sleeping
*                    time.
*       @in_src_busstop: the time of arrival at origin busstop.
*       @in_src_bus:     the time of departure time at origin busstop
*       @out_dst_bus:    the time of arrival at destiny travel.
*       @out_src_bus:    the time of departure time to the origin. 
*                       (i.e.: the start of coming back time)
*       @out_src_bus:   the time of arrival at origin.
*	@slp_bus_dst:	current thread sleep at bus in this condvar until
*			reaches its destiny.
*			(status == PASS_BUS_DST)
*	@lock_bus_dst:	needed mutex for @slp_bus_dst
*/

struct passenger {
        bus_t           *at_bus;
	uint8_t		status;
	pthread_mutex_t	lock_pass_status;
	pthread_cond_t	cond_pass_status;
        uint32_t        id_passenger;
        busstop_t       *src;
        busstop_t       *dst;
        pthread_t       *exec_passenger;
        uint32_t        sleep_time;
        struct tm	*in_src_busstop;
	struct tm       *in_src_bus;
        struct tm       *in_dst_busstop;
        struct tm       *out_dst_bus;
        struct tm       *out_src_bus;
	pthread_cond_t	slp_bus_dst;
	pthread_mutex_t	lock_bus_dst;
};

enum {
	PASS_KILL = 0,
	PASS_BLOCKED_SRC,
	PASS_WAIT_SRC,
	PASS_BUS_DST,
	PASS_DST,
	PASS_BLOCKED_DST,
	PASS_WAIT_DST,
	PASS_BUS_SRC
};

enum {
	PORT_CLOSED = 0
	PORT_DOWN,	/*passenger down from bus to busstop*/
	PORT_UP,	/*passenger up from busstop to bus*/
};

#endif /*defs.h*/
