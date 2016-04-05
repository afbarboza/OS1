#include  "passenger.h"


/**
*	init_passenger - the main function of the thread passenger.
*
*	@arg: the id of thread passenger.
*/
void *init_passenger(void *arg)
{
	return NULL;
}

/**
*	passenger_create - allocates and initializes the passenger struct
*			  corresponding to @passenger_thread.
*	
*	@passenger_thread: the corresponding thread of to be created struct
*
*	returns a pointer to the created struct or NULL, if any error 
*		occured.
*/
passenger_t *passenger_create(pthread_t *passenger_thread, uint32_t _id_passenger)
{
	passenger_t *new_pass = NULL;
	CHECK_NULL(passenger_thread, "passenger.c:23: ");

	if (_id_passenger < 0) {
		fprintf(stderr, "passenger.c:23: invalid parameter.\n");
		return NULL;
	}

	new_pass = (passenger_t *) malloc(sizeof(new_pass));
	CHECK_MEMORY(new_pass, "passenger.c:33: ");
	return NULL;
}

/**
*
*	passenger_destroy - destroys the given @passenger struct and exits
*			    the corresponding thread.
*/
void passenger_destroy(passenger_t *passenger)
{
}

/**
*
*	do_arrival - takes the @pass passenger from the @_bus and then
*		     inserts into the @stop busstop.
*/
void do_arrival(passenger_t *pass, busstop_t *stop, bus_t *_bus)
{
}

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
uint8_t at_origin(passenger_t *pass, bus_t *_bus)
{
	return 0;
}

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
uint8_t at_destiny(passenger_t *pass, bus_t *bus)
{
	return 0;
}

/**
*
*	self_passenger-	gets the corresponding struct passenger of the
*			current executing thread passenger
*/
passenger_t self_passenger(pthread_t *passenger_thread)
{
	return NULL;
}
