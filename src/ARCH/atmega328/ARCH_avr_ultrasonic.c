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
//Echo = Port D pin 5
uint8_t init_ultrassonic(void)
{
	DDRD |= (1 << PD4); //Trig as Output
	DDRD &= ~(1 << PD5); //Echo as Input
}

//
// 	// wait for any previous pulse to end
// 	while ((*portInputRegister(port) & bit) == stateMask)
// 		if (numloops++ == maxloops)
// 			return 0;
//
// 	// wait for the pulse to start
// 	while ((*portInputRegister(port) & bit) != stateMask)
// 		if (numloops++ == maxloops)
// 			return 0;
//
// 	// wait for the pulse to stop
// 	while ((*portInputRegister(port) & bit) == stateMask) {
// 		if (numloops++ == maxloops)
// 			return 0;
// 		width++;
// 	}


uint8_t read_ultrassonic(void)
{
	uint32_t temp = 0;
	uint32_t timeout = 500;
	// digitalWrite(trigPin, LOW);  // Added this line
	//   delayMicroseconds(2); // Added this line
	//   digitalWrite(trigPin, HIGH);
	// //  delayMicroseconds(1000); - Removed this line
	//   delayMicroseconds(10); // Added this line
	//   digitalWrite(trigPin, LOW);
	//   duration = pulseIn(echoPin, HIGH);
	//   distance = (duration/2) / 29.1;
	PORTD &= ~(1 << PD4);
	temp = timerOvfcnt*256 + TCNT2;
	while (timerOvfcnt*256 + TCNT2 < temp + 1);
	PORTD |= (1 << PD4);
	temp = timerOvfcnt*256 + TCNT2;
	while (timerOvfcnt*256 + TCNT2 < temp + 5);
	PORTD &= ~(1 << PD4);
	
	temp = timerOvfcnt*256 + TCNT2;
	while (PIND & (1 << PD5)) if (timerOvfcnt*256 + TCNT2 >= temp + timeout) return 0;
	temp = timerOvfcnt*256 + TCNT2;
	while (!(PIND & (1 << PD5))) if (timerOvfcnt*256 + TCNT2 >= temp + timeout) return 0;
	temp = timerOvfcnt*256 + TCNT2;
	while (PIND & (1 << PD5));
	temp = timerOvfcnt*256 + TCNT2 - temp;
	
	return temp/conversion_factor;
}
	
#ifdef __cplusplus
}
#endif