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
	
#include <ARCH_stepper.h>
#include <avr/io.h>
	
int current_position[] = {7,7};
uint16_t step_delay = 150;
uint16_t step_sz = 2000;

void init_stepper() {
	//Sets all pins to low - no movement -- RIGHT motor - But the one correspondent to the position 0 on the vector
	PORTD &= ~(1 << PD4);
	PORTC &= ~(1 << PC2);
	PORTD &= ~(1 << PD6);
	PORTD &= ~(1 << PD7);
	//Sets all pins to output
	DDRD |= (1 << DDD4);
	DDRC |= (1 << DDC2);
	DDRD |= (1 << DDD6);
	DDRD |= (1 << DDD7);
	
	//Repeat the above process on the LEFT motor
	PORTB &= ~(1 << PB0);
	PORTB &= ~(1 << PB1);
	PORTB &= ~(1 << PB2);
	PORTB &= ~(1 << PB3);
	
	DDRB |= (1 << DDB0);
	DDRB |= (1 << DDB1);
	DDRB |= (1 << DDB2);
	DDRB |= (1 << DDB3);
}

void update_stepper(int motor) {
	switch (motor) {
		case 0: //LEFT
			switch(current_position[motor]) {
				case 0:
					PORTB &= ~(1 << PB0);
					PORTB &= ~(1 << PB1);
					PORTB &= ~(1 << PB2);
					PORTB |= (1 << PB3);
					break;
				case 1:
					PORTB &= ~(1 << PB0);
					PORTB &= ~(1 << PB1);
					PORTB |= (1 << PB2);
					PORTB |= (1 << PB3);
					break;
				case 2:
					PORTB &= ~(1 << PB0);
					PORTB &= ~(1 << PB1);
					PORTB |= (1 << PB2);
					PORTB &= ~(1 << PB3);
					break;
				case 3:
					PORTB &= ~(1 << PB0);
					PORTB |= (1 << PB1);
					PORTB |= (1 << PB2);
					PORTB &= ~(1 << PB3);
					break;
				case 4:
					PORTB &= ~(1 << PB0);
					PORTB |= (1 << PB1);
					PORTB &= ~(1 << PB2);
					PORTB &= ~(1 << PB3);
					break;
				case 5:
					PORTB |= (1 << PB0);
					PORTB |= (1 << PB1);
					PORTB &= ~(1 << PB2);
					PORTB &= ~(1 << PB3);
					break;
				case 6:
					PORTB |= (1 << PB0);
					PORTB &= ~(1 << PB1);
					PORTB &= ~(1 << PB2);
					PORTB &= ~(1 << PB3);
					break;
				case 7:
					PORTB |= (1 << PB0);
					PORTB &= ~(1 << PB1);
					PORTB &= ~(1 << PB2);
					PORTB |= (1 << PB3);
					break;
				default:
					PORTB &= ~(1 << PB0);
					PORTB &= ~(1 << PB1);
					PORTB &= ~(1 << PB2);
					PORTB &= ~(1 << PB3);
					break;
			}
			break;
		case 1: //RIGHT
			switch(current_position[motor]) {
				case 0:
					PORTD &= ~(1 << PD4);
					PORTC &= ~(1 << PC2);
					PORTD &= ~(1 << PD6);
					PORTD |= (1 << PD7);
					break;
				case 1:
					PORTD &= ~(1 << PD4);
					PORTC &= ~(1 << PC2);
					PORTD |= (1 << PD6);
					PORTD |= (1 << PD7);
					break;
				case 2:
					PORTD &= ~(1 << PD4);
					PORTC &= ~(1 << PC2);
					PORTD |= (1 << PD6);
					PORTD &= ~(1 << PD7);
					break;
				case 3:
					PORTD &= ~(1 << PD4);
					PORTC |= (1 << PC2);
					PORTD |= (1 << PD6);
					PORTD &= ~(1 << PD7);
					break;
				case 4:
					PORTD &= ~(1 << PD4);
					PORTC |= (1 << PC2);
					PORTD &= ~(1 << PD6);
					PORTD &= ~(1 << PD7);
					break;
				case 5:
					PORTD |= (1 << PD4);
					PORTC |= (1 << PC2);
					PORTD &= ~(1 << PD6);
					PORTD &= ~(1 << PD7);
					break;
				case 6:
					PORTD |= (1 << PD4);
					PORTC &= ~(1 << PC2);
					PORTD &= ~(1 << PD6);
					PORTD &= ~(1 << PD7);
					break;
				case 7:
					PORTD |= (1 << PD4);
					PORTC &= ~(1 << PC2);
					PORTD &= ~(1 << PD6);
					PORTD |= (1 << PD7);
					break;
				default:
					PORTD &= ~(1 << PD4);
					PORTC &= ~(1 << PC2);
					PORTD &= ~(1 << PD6);
					PORTD &= ~(1 << PD7);
					break;
			}
			break;
	}
}

void forward_stepper(int motor)
{
	current_position[motor]++;
	current_position[motor]%=8;
	update_stepper(motor);
	// printnum(motor);
	// print("-");
	// printnum(current_position[motor]);
}

void backward_stepper(int motor)
{
	current_position[motor]--;
	if (current_position[motor] < 0) current_position[motor]+= 8;
	update_stepper(motor);
}

void stop_stepper(int motor) {
	switch (motor) {
		case 0: //LEFT
			PORTB &= ~(1 << PB0);
			PORTB &= ~(1 << PB1);
			PORTB &= ~(1 << PB2);
			PORTB &= ~(1 << PB3);
			break;
		case 1: //RIGHT
			PORTD &= ~(1 << PD4);
			PORTC &= ~(1 << PC2);
			PORTD &= ~(1 << PD6);
			PORTD &= ~(1 << PD7);
			break;
	}
}
	
#ifdef __cplusplus
}
#endif