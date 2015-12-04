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

#include <timer.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <HAL.h>

void init_timer(void)
{
	uint16_t prescaler = best_PS();//CHAMAR FUNCAO
	uint32_t comparer = 0;
	while (prescaler != 1 && prescaler != 8 && prescaler != 32 && prescaler != 64 && prescaler != 128 && prescaler != 256 && prescaler != 1024)
	{
		prescaler = prescaler << 1;
	}
	comparer = ((F_CPU/prescaler)/F_INT);
	while (comparer > 255)
	{
		comparer = comparer >> 1;
		threshold = threshold << 1;
	}
	
	TCCR2B |= ((prescaler >= 64) << CS22) | ((prescaler==8 || prescaler==32 || prescaler==256 || prescaler==1024) << CS21) | ((prescaler==1 || prescaler==32 || prescaler==128 || prescaler==1024) << CS20);
	OCR2A = comparer;
	OCR2B = comparer;
	TCNT2 = 0;
	TIMSK2 |= (1 << OCIE2A) | (1 << TOIE2);
	
	sei();
	
	printnum(TIMSK2);
	print("\n");
	printnum(OCR2A);
	print("\n");
	printnum(TCCR2B);
	print("\n");
	// PORTB |= (1 << PB5);
}

ISR(TIMER2_OVF_vect)
{
	timerOvfcnt++;
}
	
ISR(TIMER2_COMPA_vect)
{
	// PORTB |= (1 << PB5);
	counter++;
	if (counter == threshold)
	{
		// CALL FUNCTION ->Set variable
		PORTB ^= (1 << PB5);
		counter = 0;
	}
}

#ifdef __cplusplus
}
#endif