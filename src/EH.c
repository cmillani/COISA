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
	
#include <EH.h>

void (*ehvec[EHVECSZ])(void) = {0};
uint8_t vec_size = 0;
uint8_t ehqueue[EHQUEUESZ] = {0};
uint8_t queue_init = 0;
uint8_t queue_size = 0;
uint8_t timer_flag = 0;
ev_point ehvecpointers[EVENTQTTY];

void eh_init(void)
{
	//initialize timer - HAL WORK
	
	/*Initializes the event descriptors*/
	register uint8_t i = 0;
	for (i = 0; i < EVENTQTTY; i++)
	{
		ehvecpointers[i].id = -1;
		ehvecpointers[i].pos = 0;
		ehvecpointers[i].sz = 0;
	}
	/*---------------------------------*/
}


int8_t register_handler(uint8_t event_id, void (*handler)(void), ...)
{
	if (!(vec_size < EHVECSZ)) return -2; //No space for one more handler
	register int8_t selected;
	for (selected = 0; selected < EVENTQTTY; selected++)
	{
		if (ehvecpointers[selected].id == event_id) break; //Selected is now the position of the event on the vector
	}
	if (ehvecpointers[selected].id != event_id) //Case where there was no break, thus no match was found
	{
		for (selected = 0; selected < EVENTQTTY; selected++)//Searches for the first empty space
		{
			if (ehvecpointers[selected].id == -1) break; //Selected is now the position of the first empty slot on the array
		}
		if (ehvecpointers[selected].id != -1) return -1;//No empty space
		ehvecpointers[selected].id = event_id; //marks the empty space as the new event
		ehvecpointers[selected].pos = vec_size; //Position for the first handler = end of the vector
	}
	if (ehvec[ehvecpointers[selected].pos] == 0) //No handler in the position after the last handler of this event
	{
		ehvec[ehvecpointers[selected].pos] = handler;
	}
	else //Shift all right to get space
	{
		
	}
	//Creates handler
	
	
	//Remember to tell HAL to generate events!
	
	ehvecpointers[selected].sz++;
	vec_size++;
	return 1;
}
int8_t remove_handler(uint8_t event_id, void (*handler)(void))
{
	register int8_t selected;
	for (selected = 0; selected < EVENTQTTY; selected++)
	{
		if (ehvecpointers[selected].id == event_id) break; //Selected is now the position of the event on the vector
	}
	if (ehvecpointers[selected].id != event_id) return -1; //No such handler
	
	//Removes handler and check if event is still generating events -- VERIFY HAL after removing, should stop generating events?
	
	
	vec_size--;
	return 1;
}
void __inline__ event_timer(void)
{
	timer_flag = 1; //Set flag to true
}


int8_t insert_event(uint8_t event_id)
{
	if (queue_size < EHQUEUESZ) //Still has space
	{
		ehqueue[(queue_init + queue_size) % EHQUEUESZ] = event_id; //Its a vector list
		queue_size++; 
		return 1; //Success
	}
	else return -1; // No space, returns error
}
int8_t consume_event()
{
	if (queue_size > 0) //Has something
	{
		register int8_t selected;
		{ //Block used to scope the event variable
			register uint8_t event = ehqueue[queue_init];
			queue_size--;
			queue_init++; //Pops the first value and updates 
		
			//Gets the event pointer to
			for (selected = 0; selected < EVENTQTTY; selected++)
			{
				if (ehvecpointers[selected].id == event) break; //Selected is now the position of the event on the vector
			}
			if (ehvecpointers[selected].id != event) return -1; //No event with that id found -- ERROR
		}
		register  uint8_t loop;
		for (loop = ehvecpointers[selected].pos; loop < ehvecpointers[selected].sz; loop++)
		{
			//cpu(ehvec[loop]); // Should call CPU this way, sending the address to the function
		}
		return 1; // Success
	}
	else return -1; //Nothing to Consume
}

	
#ifdef __cplusplus
}
#endif