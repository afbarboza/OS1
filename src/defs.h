#ifndef DEFS_H
#define	DEFS_H

#include <pthread.h>
#include <stdint.h>
#include "list.h"

typedef struct busstop		busstop_t;
typedef struct bus 		bus_t;
typedef	struct passenger	passenger_t;

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
        uint8_t         ready_to_go;
        pthread_t       *exec_bus;
};

/**
*       struct passengers - all the info about the citizens who are
*                     circulating at the city.
*
*       @at_bus: pointer to bus that passenger is currently riding.
*               (ENOATBUS if passenger is not at bus).
*
*       @blocked: flag indicating whether the passenger is 
*                 sleeping at destiny.
*       @at_dest: flag indicating whteher passenger already arrived
*                 at the destiny.
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
        uint8_t         blocked;
        uint8_t         at_dst;
        uint32_t        id_passenger;
        busstop_t       *src;
        busstop_t       *dst;
        pthread_t       *exec_passenger;
        uint32_t        sleep_time;
        clock_t         in_src_busstop;
        clock_t         in_src_bus;
        clock_t         in_dst_busstop;
        clock_t         out_dst_bus;
        clock_t         out_src_bus;
};

#endif /*defs.h*/
