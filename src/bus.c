#include <stdint.h>
#include <pthread.h>
#include "defs.h"
	
void *init_bus(void *arg){
	
}

bus_t bus_create( pthread_t *bus_thread ){
	
	n_seats =  A; 						//variavel global que contem o numero de assentos em cada onibus
	
	id_bus = ;				//atribui o id da thread que criou o onibus ao onibus
	
	critical_stopped = ENOBUSSTOP;		//quando o onibus eh criado ele ainda nao e linkado a um ponto
	
	*critical_seats = (passenger*)(malloc(A*sizeof(passenger)));;		// cria a fila na qual os passageiros sao armazenados
	
	critical_available_seats = A;		// no comeco o numero de asentos livre eh igual ao total de asentos
	
	ready_to_go = EFULLBUS;				// sinaliza que o onibus esta pronto para receber passageiros
	
	*exec_bus = bus_thread;				// armazena a thread que sera responsavel por trabalhar com esse onibus
	
	// CADE O RETORNO DESSA FUNCAO?	
 }
 
void bus_destroy(bus_t *_bus){
	free(_bus->critical_available_seats);
	free( _bus->exec_bus );
	list_destroy( _bus->critical_seats );
	// onde vc tá matando a thread??????
 }
 

/**
*	at_busstop - checks whether a given @_bus is stopped.
*	
*	returns 1 if is stopped, 0 otherwise.
*/
uint8_t at_busstop(bus_t *_bus){
	
	return ((_bus->critical_stopped) ? 1 :0);

 }
 
/**
*	full_bus - checks wheter exists at least one available seat
*
*	returns 1, if the given bus is not full
*		0, otherwise.
*/
uint8_t full_bus(bus_t *_bus);{
	
	return (( _bus->critical_available_seats != ENOBUSSTOP ) ? 1 :0);

 }
 
/**
*
*	receive_passenger - allocates one seat to the most recently 
*			    @passenger entered at the @_bus.
*
*	@_bus: the bus which will receive the new passenger.
*	@pass: the entered passenger.
*/
void receive_passenger(bus_t *_bus, passenger_t *pass){
	int i;
	if( _bus->critical_available_seats > 0 ){
		for( i = 0 ; i < A ; i++ ){
			if( _bus->critical_seats[i] == NULL ){
				_bus->critical_seats[i] = pass;
				i = A;
			}
		}	
	}
}

/**
*	send_passenger: sends a passenger to the busstop which @bus is it.	
*/
void send_passenger(bus_t *bus, busstop_t *_busstop ){
	int i;
	if( _bus->critical_available_seats > 0 ){
		for( i = 0 ; i < A ; i++ ){
			if( _bus->critical_seats[i] != NULL )
				if( _bus->critical_seats[i].src == bus->critical_stopped && _bus->critical_seats[i].at_dest == 0 ){
					acquire_passenger( _busstop, _bus->critical_seats[i] );
				}else if( _bus->critical_seats[i].dst == bus->critical_stopped && _bus->critical_seats[i].at_dest == 1 ){
					acquire_passenger( _busstop, _bus->critical_seats[i] );
				}
		}	
	}
}
