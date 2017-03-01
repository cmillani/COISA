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

#include <inttypes.h>
#include <avr/io.h>
#include <timer.h>
#include <HAL.h>
#include <ultrasonic.h>
//Trig = Port D pin 4
//Echo = Port D pin 5
	

#define us_debouncing_time 1000

uint32_t us_timestamp = 0;
	
uint8_t init_ultrassonic(void)
{
	us_timestamp = timer_get_ticks();
	DDRD |= (1 << PD2); //Trig as Output -- Arduino pin
	DDRD &= ~(1 << PD3); //Echo as Input
}

#include <serial.h>

uint8_t last_read = ~0;

uint8_t read_ultrassonic(void)
{
	if (timer_get_ticks() - us_timestamp < us_debouncing_time) return last_read;
	us_timestamp = timer_get_ticks();
	uint32_t temp = 0; //Used to store time along the function
	uint32_t timeout = 8000;

	PORTD &= ~(1 << PD2); //First sets to zero the trig pin
	temp = timer_get_ticks(); 
	while (timer_get_ticks() < temp + 1); //Waits 2us
	PORTD |= (1 << PD2); //Sends Pulse through trig pin
	temp = timer_get_ticks();
	while (timer_get_ticks() < temp + 5); //Pulse has the duration of 10us
	PORTD &= ~(1 << PD2); //Sets pin to low again
	
	//Here we have the timeout to prevent an infinite loop
	temp = timer_get_ticks();
	while (PIND & (1 << PD3)) if (timer_get_ticks() >= temp + timeout) return 255; //Wait until echo is low
	temp = timer_get_ticks();
	while (!(PIND & (1 << PD3))) if (timer_get_ticks() >= temp + timeout) return 255; //Wait until echo is high
	temp = timer_get_ticks();
	while (PIND & (1 << PD3)) if (timer_get_ticks() >= temp + timeout) return 255; //Starts counting until echo is low again
	temp = timer_get_ticks() - temp;//Gets the high time of the pulse
	last_read = temp/conversion_factor;
	return last_read;//Converts it to the configured Unit System
}
	
#ifdef __cplusplus
}
#endif