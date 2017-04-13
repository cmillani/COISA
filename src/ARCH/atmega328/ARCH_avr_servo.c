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

#include <ARCH_servo.h>	 
#include <avr/io.h>
#include <stdint.h>
#include <timer.h>
#include <serial.h>
	
void init_servo(void) {
	DDRD |= (1 << PD5); //OUTPUT
	PORTD &= ~(1 << PD5); //OFF
	TCCR0A |= (1 << WGM01) | (1 << WGM00); //PWM GENERATION ON
	TCCR0B |= (1 << CS02) | (1 << CS00); //TIMER PRESCALED
	OCR0B = 0; //PWM SET TO ZERO BUT STILL OFF ON THIS PIN
}

void servo_up(void) {
	TCCR0A |= (1 << COM0B1);
	OCR0B = 10;
	uint32_t timestamp_servo = timer_get_ticks();
	uint32_t now = timestamp_servo;
	// printnum(timestamp_servo);
	// print("\n");
	// printnum(now);
	// print("\n");
	while (now - timestamp_servo < 300000UL){
		// print("In");
		now = timer_get_ticks();
	}
	// printnum(timestamp_servo);
	// print("\n");
	// printnum(now);
	// print("\n");
	TCCR0A &= ~(1 << COM0B1);
}

void servo_down(void) {
	TCCR0A |= (1 << COM0B1);
	OCR0B = 25;
	uint32_t timestamp_servo = timer_get_ticks();
	uint32_t now = timestamp_servo;
	// printnum(timestamp_servo);
	// print("\n");
	// printnum(now);
	// print("\n");
	while (now - timestamp_servo < 300000UL){
		// print("In");
		now = timer_get_ticks();
	}
	// printnum(timestamp_servo);
	// print("\n");
	// printnum(now);
	// print("\n");
	TCCR0A &= ~(1 << COM0B1);
}
	
#ifdef __cplusplus
}
#endif