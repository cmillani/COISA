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

#include <TM.h>
#include <HAL.h>
#include <EH.h>
#include <vm.h>
#include <inttypes.h>

uint32_t tm_counter = 0;

void (*state)(void);

void idle(void) {
	//TODO: should sleep here :)
}
	
void receiving_x(void) {
	
}

void executing(void) {
	
}

void stopping(void) {
	
}

void tm_init(void) {
	/*COISA's Initialization*/
	eh_init();
	serial_configure(9600);
	init_timer();
	start_encoder();
	/*Everything initialized*/
	state = idle;
	while(1)
	{
		if (has_command)
		{
			has_command = 0;
			print("HAHAHA\n");
		}
	}
	/*Coisa VM cpu, HAL, EH and TM loop*/
    while(1)
    {
		state();
		if(timer_flag) 
		{
			tm_counter++;
			timed_polling();
			timer_flag = 0;
			if (tm_counter >= 4) //Every 4 timer interruptions, should check for PID controlling
			{
				PID();
				tm_counter = 0;
			}
		}
		consume_event();
	}
}
	
#ifdef __cplusplus
}
#endif
	