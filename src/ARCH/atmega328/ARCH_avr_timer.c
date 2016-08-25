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
#include <EH.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <HAL.h>

void init_timer(void)
{	
	TCCR2B |= (1 << CS21) | (1 << CS20); //Prescaler = 32
	TCNT2 = 0;
	TIMSK2 |= (1 << TOIE2);
	sei();
}

uint32_t timer_get_ticks(void) {
	return timerOvfcnt*256 + TCNT2;
}

ISR(TIMER2_OVF_vect)
{
	timerOvfcnt++;
	int32_t temp = timerOvfcnt;
	if ((int)temp % (50*(F_CPU/8192))==0)
	{
		event_timer();
	}
}

#ifdef __cplusplus
}
#endif