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
#include <ultrasonic.h>
//Trig = Port D pin 4
//Echo = Port D pin 7
uint8_t init_ultrassonic(void)
{
	DDRD |= (1 << PD4); //Trig as Output
	DDRD &= ~(1 << PD7); //Echo as Input
}

#include <serial.h>
uint8_t read_ultrassonic(void)
{
	uint32_t temp = 0; //Used to store time along the function
	uint32_t timeout = 8000;

	PORTD &= ~(1 << PD4); //First sets to zero the trig pin
	temp = timerOvfcnt*256 + TCNT2; 
	while (timerOvfcnt*256 + TCNT2 < temp + 1); //Waits 2us
	PORTD |= (1 << PD4); //Sends Pulse through trig pin
	temp = timerOvfcnt*256 + TCNT2;
	while (timerOvfcnt*256 + TCNT2 < temp + 5); //Pulse has the duration of 10us
	PORTD &= ~(1 << PD4); //Sets pin to low again
	
	//Here we have the timeout to prevent an infinite loop
	temp = timerOvfcnt*256 + TCNT2;
	while (PIND & (1 << PD7)) if (timerOvfcnt*256 + TCNT2 >= temp + timeout) return 255; //Wait until echo is low
	temp = timerOvfcnt*256 + TCNT2;
	while (!(PIND & (1 << PD7))) if (timerOvfcnt*256 + TCNT2 >= temp + timeout) return 255; //Wait until echo is high
	temp = timerOvfcnt*256 + TCNT2;
	while (PIND & (1 << PD7)) if (timerOvfcnt*256 + TCNT2 >= temp + timeout) return 255; //Starts counting until echo is low again
	temp = timerOvfcnt*256 + TCNT2 - temp;//Gets the high time of the pulse
	return temp/conversion_factor;//Converts it to the configured Unit System
}
	
#ifdef __cplusplus
}
#endif