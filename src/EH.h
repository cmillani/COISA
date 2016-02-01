/***************************************************************************
 *   Copyright (C) 2015 by                                                 *
 *   - Carlos Eduardo Millani (carloseduardomillani@gmail.com)             *
 *   - Edson Borin (edson@ic.unicamp.br)                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef EH_H
#define EH_H

#include "config.h"
#include <inttypes.h>

extern volatile uint8_t timer_flag; //Flag to indicate that data must be processed

/*
	The id is first -1, showing that there is still space for one more event to be handled.
Once an event handler for a new event must be registered, we search for an empty event (id = -1)
and use it, changing it`s ID to the one of the new event.
*/
typedef struct event_point
{
	int8_t id;
	char name[5];
	uint8_t pos;
	uint8_t sz;
} ev_point;

typedef struct event
{
	volatile uint8_t id;
	char name[5];
} new_event;

/*
		DESCRIPTION:
	There are 3 vectors: the vector of handlers, the queue of events and a pointer to the handler of an event.
The vector of handlers has the address of the function that is called when an event is generated.
The queue of events is a FIFO data structure responsible for holding the generated events until they are consumed.
The last one, the pointer vector, holds the number of handlers and the position of the handler in the first vector for all the registered events.
One event may have more than one handler, that`s why there are more than one structure to hold the handler`s info.
*/


#define EHVECSZ 5 //Size of the vector of handlers
#define EHQUEUESZ 3 //Size of the event queue
extern uint32_t ehvec[EHVECSZ]; //Vector of handlers
extern new_event ehqueue[EHQUEUESZ]; //Events queue	
volatile extern uint8_t queue_init;
volatile extern uint8_t queue_size;

#define EVENTQTTY 3 //Number of different events that can be generated
extern ev_point ehvecpointers[EVENTQTTY]; //Pointer to the part of the handler vector that corresponds to that event

/*******************************************************************/
/*******************************************************************/
#if HAS_ULTRASONIC
#include <ultrasonic.h>
#endif 
/*******************************************************************/
/*******************************************************************/


void print_EH(void);

/********************************************************************
** timed_polling(void)                                             **
**                                                                 **
** Poll some sensor values                                         **
********************************************************************/
void timed_polling(void);

/********************************************************************
** eh_init(void)                                                   **
**                                                                 **
** Configures HAL and initilizes variables in order to start EH    **
********************************************************************/
void eh_init(void);

/********************************************************************
** register_handler(uint8_t event_id, void (*handler)(void), ...)  **
**                                                                 **
** PARAMS:                                                         **
** event_id: the id of the event receiving the handler             **
** handler: pointer to the handler function                        **
** (...) extra paramaters that vary accordingly to the event       **
**    (see HAL)                                                    **
**                                                                 **
** RETURNS:                                                        **
** -1 no space for one mor handler error                           **
** 1 success                                                       **
**                                                                 **
** DESCRIPTION:                                                    **
** Register 'handler' as a callback to be executed when the event  **
** of id 'event_id' happens                                        **
********************************************************************/
int8_t register_handler(uint8_t event_id, uint32_t handler, char * evname, void * argv[], uint8_t argc);

/********************************************************************
** remove_handler(uint8_t event_id, void (*handler)(void))         **
**                                                                 **
** PARAMS:                                                         **
** event_id: the id of the event receiving the handler             **
** handler: pointer to the handler function                        **
**                                                                 **
** RETURNS:                                                        **
** -1 handler or event not registered                              **
** 1 success                                                       **
**                                                                 **
** DESCRIPTION:                                                    **
** removes 'handler' from the handler vector                       **
********************************************************************/
int8_t remove_handler(uint8_t event_id, uint32_t handler, char * evname);

/********************************************************************
** event_timer(void)                                               **
**                                                                 **
** Function to be executed from time to time, using a hardware     **
**   clock. Responsible for polling and processing data from some  **
**   sensors.                                                      **
********************************************************************/
void event_timer(void); //To be called by the timer and then process data from sensors and (maybe) generate events

/********************************************************************
** insert_event(uint8_t event_id)                                  **
**                                                                 **
** Used to register on the queue an event of the id 'event_id'     **
********************************************************************/
int8_t insert_event(uint8_t event_id, char * evname); //Generates an event

/********************************************************************
** consume_event(void)                                             **
**                                                                 **
** RETURNS:                                                        **
** 1  success                                                      **
** -1 error                                                        **
**                                                                 **
** Tells the EH to consume the next event on the queue             **
********************************************************************/
int8_t consume_event(void); //Gets the id of the next event to be handled

#endif // EH_H

#ifdef __cplusplus
}
#endif