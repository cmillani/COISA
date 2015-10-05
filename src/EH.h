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

extern uint8_t timer_flag; //Flag to indicate that data must be processed

/*
	The id if first -1, showing that there is still space for one more event to be handled.
Once an event handler for a new event must be registered, we search for an empty event (id = -1)
and use it, changing it`s ID to the one of the new event.
*/
typedef struct event_point
{
	int8_t id;
	uint8_t pos;
	uint8_t sz;
} ev_point;

#define EHVECSZ 10 //Size of the vector of handlers
#define EHQUEUESZ 10 //Size of the event queue
extern void (*ehvec[EHVECSZ])(void); //Vector of handlers
extern uint8_t ehqueue[EHQUEUESZ]; //Event handlers queue	
extern uint8_t queue_init;
extern uint8_t queue_size;

#define EVENTQTTY 4 //Number of different events that can be ganerated
extern ev_point ehvecpointers[EVENTQTTY]; //Pointer to the part of the vector that corresponds to that event

void eh_init(void); //Initializes the environment

int8_t register_handler(uint8_t event_id, void (*handler)(void), ...); //Registers the given function to handle the especified event, returns the handler_id (eventid*eventnumber)
int8_t remove_handler(uint8_t event_id, void (*handler)(void)); //Removes a handler from a determined event
void __inline__ event_timer(void); //To be called by the timer and then process data from sensors and (maybe) generate events

int8_t insert_event(uint8_t event_id); //Generates an event
int8_t consume_event(); //Gets the id of the next event to be handled

#endif // EH_H

#ifdef __cplusplus
}
#endif