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
#include <vm.h>
#include <stdutils.h>
#include <HAL.h>
// #include <stdarg.h>
//
// #include <stdio.h>
// void print_EH(void)
// {
// 	printf("*---------------------------------------------------------*\n");
// 	printf("EH:\n");
// 	printf("Events:\t");
// 	for (int i = 0; i < EVENTQTTY; i++)
// 	{
// 		printf("%d,%d,%d, %s\t", ehvecpointers[i].id, ehvecpointers[i].pos, ehvecpointers[i].sz, ehvecpointers[i].name);
// 	}
// 	printf("\n");
// 	printf("Handlers:\t");
// 	for (int i = 0; i < EHVECSZ; i++)
// 	{
// 		printf("%d\t", ehvec[i]);
// 	}
// 	printf("\n");
// 	printf("Queue:\t");
// 	for (int i = 0; i < EHQUEUESZ; i++)
// 	{
// 		printf("%d, %s\t", ehqueue[i].id, ehqueue[i].name);
// 	}
// 	printf("Init:%d,Sz:%d\n", queue_init, queue_size);
// 	printf("*---------------------------------------------------------*\n");
// }

uint32_t ehvec[EHVECSZ] = {0};
uint8_t vec_size = 0;
new_event ehqueue[EHQUEUESZ] = {0};
volatile uint8_t queue_init = 0;
volatile uint8_t queue_size = 0;
volatile uint8_t timer_flag = 0;
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


int8_t register_handler(uint8_t event_id, uint32_t handler, char * evname, void * argv, uint8_t argc)
{
	if (!(vec_size < EHVECSZ)) return -1; //No space for one more handler
	register uint8_t selected;
	for (selected = 0; selected < EVENTQTTY; selected++)
	{
		if (ehvecpointers[selected].id == event_id && !strcmp(ehvecpointers[selected].name,evname)) break; //Selected is now the position of the event on the vector
	}
	if (ehvecpointers[selected].id != event_id || strcmp(ehvecpointers[selected].name,evname)) //Case where there was no break, thus no match was found
	{
		for (selected = 0; selected < EVENTQTTY; selected++)//Searches for the first empty space
		{
			if (ehvecpointers[selected].id == -1) break; //Selected is now the position of the first empty slot on the array
		}
		if (ehvecpointers[selected].id != -1) return -1;//No empty space
		ehvecpointers[selected].id = event_id; //marks the empty space as the new event
		strcpy(ehvecpointers[selected].name, evname);
		for (ehvecpointers[selected].pos = 0; ehvecpointers[selected].pos < EHVECSZ; ehvecpointers[selected].pos++)
		{
			if (ehvec[ehvecpointers[selected].pos] == 0) break;
		}//Gets the first free position for the new event
		
	}
	if (ehvec[ehvecpointers[selected].pos + ehvecpointers[selected].sz] == 0) //No handler in the position after the last handler of this event
	{
		ehvec[ehvecpointers[selected].pos + ehvecpointers[selected].sz] = handler;
	}
	else //Shift to get space
	{
		register uint8_t first_zero;
		register uint8_t idnearfz;
		for (first_zero = 0; first_zero < EHVECSZ; first_zero++)
		{
			if (ehvec[first_zero] == 0) break;
		}//find first empty, check which event it is from, then shift... firstzero>pos and <= pos+sz
		if (first_zero < ehvecpointers[selected].pos) // the empty space is before the event, should shift left
		{
			for (idnearfz = 0; idnearfz < selected; idnearfz++) //To set idnearfz
			{
				if(first_zero < ehvecpointers[idnearfz].pos + ehvecpointers[idnearfz].sz -1) break; //Ensures that the first zero is on that id
			}
			for (;idnearfz <= selected; idnearfz++) //Starts shifting id by id
			{
				ehvec[first_zero] = ehvec[ehvecpointers[idnearfz].pos + ehvecpointers[idnearfz].sz -1];
				ehvec[ehvecpointers[idnearfz].pos + ehvecpointers[idnearfz].sz -1] = 0;
				first_zero = ehvecpointers[idnearfz].pos + ehvecpointers[idnearfz].sz -1;
				ehvecpointers[idnearfz].pos--;
			}
			ehvec[ehvecpointers[selected].pos + ehvecpointers[selected].sz] = handler;
		}
		else if (first_zero > ehvecpointers[selected].pos + ehvecpointers[selected].sz)
		{
			for (idnearfz = EVENTQTTY-1; idnearfz > selected; idnearfz--) //To set idnearfz
			{
				if (ehvecpointers[idnearfz].id == -1) continue; //Position not used
				if(first_zero > ehvecpointers[idnearfz].pos + ehvecpointers[idnearfz].sz -1) break; //Ensures that the first zero is on that id
			}
			for (;idnearfz > selected; idnearfz--) //Starts shifting id by id
			{
				ehvec[first_zero] = ehvec[ehvecpointers[idnearfz].pos];
				ehvec[ehvecpointers[idnearfz].pos] = 0;
				first_zero = ehvecpointers[idnearfz].pos;
				ehvecpointers[idnearfz].pos++;
			}
			ehvec[ehvecpointers[selected].pos + ehvecpointers[selected].sz] = handler;
		}
		else //Should never get here
		{
			return -3;
		}
		
	}
	
#if HAS_ULTRASONIC
	// print("Uhm\n");
	if (!strcmp(evname, "US_S")) //US dist sensor has the threshold argument
	{
		// print("IuhullUM\n");
		if (argc == 1)
		{
			// printnum(((int*)argv)[0]);
			// print("<<Iuhull\n");
			us_threshold = ((int*)argv)[0];
		}
	}
#endif
	
	//TODO:Remember to tell HAL to generate events! -- Currently it always generate events
	
	ehvecpointers[selected].sz++;
	vec_size++;
	return 1;
}
int8_t remove_handler(uint8_t event_id, uint32_t handler, char * evname)
{
	register int8_t selected;
	for (selected = 0; selected < EVENTQTTY; selected++)
	{
		if (ehvecpointers[selected].id == event_id && !strcmp(ehvecpointers[selected].name,evname)) break; //Selected is now the position of the event on the vector
	}
	if (ehvecpointers[selected].id != event_id || strcmp(ehvecpointers[selected].name,evname)) return -1; //No such event

	register int8_t event;
	for (event = ehvecpointers[selected].pos; event < ehvecpointers[selected].sz; event++)
	{
		if (ehvec[event] == handler) break;
	}
	if (ehvec[event] != handler) return -1; //No such handler
	
	
	ehvec[event] = ehvec[ehvecpointers[selected].pos + ehvecpointers[selected].sz -1]; //Make sure there won`t be a gap in the vector
	ehvec[ehvecpointers[selected].pos + ehvecpointers[selected].sz - 1] = 0;
	
	if (--ehvecpointers[selected].sz == 0) //Became empty
	{
		ehvecpointers[selected].id = -1;
		ehvecpointers[selected].pos = 0;
	}
	
	//TODO:VERIFY HAL after removing, should stop generating events?
	
	
	vec_size--;
	return 1;
}
void event_timer(void)
{
	timer_flag = 1; //Set flag to true
}


int8_t insert_event(uint8_t event_id, char * evname)
{
	if (queue_size < EHQUEUESZ) //Still has space
	{
		ehqueue[(queue_init + queue_size) % EHQUEUESZ].id = event_id; //Its a vector list
		strcpy(ehqueue[(queue_init + queue_size) % EHQUEUESZ].name, evname);
		queue_size++;
		return 1; //Success
	}
	else return -1; // No space, returns error
}
int8_t consume_event(void) //TODO:For some reason i cannot print from inside this func
{
	if (queue_size > 0) //Has something
	{
		register int8_t selected;
		{ //Block used to scope the event variable
			new_event event = ehqueue[queue_init];
			queue_size--;
			queue_init = (queue_init+1)%(EHQUEUESZ); //Pops the first value and updates

			//Gets the event pointer to
			for (selected = 0; selected < EVENTQTTY; selected++)
			{
				if (!strcmp(ehvecpointers[selected].name,event.name)) break; //Selected is now the position of the event on the vector
			}
			if (strcmp(ehvecpointers[selected].name,event.name) ) return -1; //No event with that id found -- ERROR
		}
		register  uint8_t loop;
		for (loop = ehvecpointers[selected].pos; loop < ehvecpointers[selected].pos + ehvecpointers[selected].sz; loop++)
		{
			RF[4] = ehvec[loop];
			vm_init(hand_addr);
			vm_cpu();
		}
		return 1; // Success
	}
	else return -1; //Nothing to Consume
}

void timed_polling(void)
{
#if HAS_ULTRASONIC
	// printnum(read_ultrassonic());
	// print("<<\n");
	uint8_t dist = read_ultrassonic();
	if (dist < us_threshold - 1) //Hysteresis
	{
		if (!is_close)
		{
			is_close = 1;
			insert_event(1,"US_S");
		}
	}
	else if (dist > us_threshold + 1)
	{
		if (is_close)
		{
			is_close = 0;
			insert_event(1,"US_F");
		}
	}
#endif 
}

	
#ifdef __cplusplus
}
#endif