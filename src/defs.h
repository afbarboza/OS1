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


typedef struct busstop		busstop_t;
typedef struct bus 		bus_t;
typedef	struct passenger	passenger_t;

pthread_t *thread_bus;
pthread_t *thread_busstop;
pthread_t *thread_passengers;

bus_t 		*bus_s;		/*array of global structures bus*/
busstop_t 	*busstop_s;	/*array of global structures busstop*/
passenger_t 	*passenger_s;	/*array of global strucutures passengers*/


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
*
*/

struct busstop {
        uint32_t        id_bustop;
        bus_t           *critical_busy_bus;
        uint32_t        passenger;
        uint8_t         port_status;
        pthread_t       *exec_busstop;
        struct list     *critical_ready_passengers;
        struct list     *critical_blocked_passengers;
};

/**
*       struct bus - the infos about the circulating bus at town.
*
*       @n_seats: the number of available seats when the bus is empty.
*       @id_bus:  the unique identifiqer of bus
*       @busstop: pointer to which busstop the current bus is.
*                 (or ENOSTOPBUS if not stopped at none of busstop)
*       @seats:   pointer to the passengers who are riding at that bus.
*       @available_seats: @n_seats minus the amount of riding pasengers
*       @ready_to_go: flag indicating whhether there is no departing or
*                     arriving passengers to be done. (ERDYTOGO if so)
*       @exec_bus: pointer to the current thread of bus which is being 
*                  manipulated. 
*/
struct bus {
        uint32_t        n_seats;
        uint32_t        id_bus;
        busstop_t       *critical_stopped;
        passenger_t     *critical_seats;
        uint32_t        critical_available_seats;
        //uint8_t         ready_to_go;
        pthread_t       *exec_bus;
};

/**
*       struct passengers - all the info about the citizens who are
*                     circulating at the city.
*
*       @at_bus: pointer to bus that passenger is currently riding.
*               (ENOATBUS if passenger is not at bus).
*	@status: state of thread passenger in the process
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
*/

struct passenger {
        bus_t           *at_bus;
	uint8_t		status;
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
};

enum {
	PASS_KILL = 0,
	PASS_BLOCKED_SRC,
	PASS_WAIT_SRC,
	PASS_BUS_DST,
	PASS_DST,
	PASS_WAIT_DST,
	PASS_BUS_SRC
};

#endif /*defs.h*/
