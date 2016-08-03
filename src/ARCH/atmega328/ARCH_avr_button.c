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
	
#include <ARCH_button.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <EH.h>
#include <HAL.h>
#include <timer.h>
	
#define debouncing_time 100000
	
uint8_t initialized;
uint8_t mode;
volatile uint32_t timestamp = 0;
//TODO: save each pin initialized
volatile uint8_t current_pin;
volatile uint8_t current_port;

void init_button(uint8_t port, uint8_t pin)
{
	current_pin = pin;
	timestamp = timerOvfcnt*256 + TCNT2;
	if (port == BPORT)
	{
		current_port = BPORT;
		PORTB |= (1 << pin);
		DDRB &= ~(1 << pin);
		PCICR |= (1 << PCIE0);
		PCMSK0 |= (1 << pin);
		sei();
		initialized = 1;
	}
	else if (port == CPORT)
	{
		current_port = CPORT;
		PORTC |= (1 << pin);
		DDRC &= ~(1 << pin);
		PCICR |= (1 << PCIE1);
		PCMSK1 |= (1 << pin);
		sei();
		initialized = 1;
	}
	else if (port == DPORT)
	{
		current_port = DPORT;
		PORTD |= (1 << pin);
		DDRD &= ~(1 << pin);
		PCICR |= (1 << PCIE2);
		PCMSK2 |= (1 << pin);
		sei();
		initialized = 1;
	}
}

ISR(PCINT0_vect)
{
	if (timerOvfcnt*256 + TCNT2 - timestamp > debouncing_time)
	{
		timestamp = timerOvfcnt*256 + TCNT2;
		if (current_port == DPORT && PIND & (1 << current_pin)) return;
		if (current_port == CPORT && PINC & (1 << current_pin)) return;
		if (current_port == BPORT && PINB & (1 << current_pin)) return;
		insert_event(1,"BTOG");
	}
}
ISR(PCINT1_vect, ISR_ALIASOF(PCINT0_vect));
ISR(PCINT2_vect, ISR_ALIASOF(PCINT0_vect));
	
#ifdef __cplusplus
}
#endif