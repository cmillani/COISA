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

#include <avr/io.h>  
#include "ARCH_PWM.h"
    
#define ARDUINO_3  19
#define ARDUINO_5  21
#define ARDUINO_6  22
#define ARDUINO_9  1
#define ARDUINO_10 2
#define ARDUINO_11 3
    
void set_PWM(int pin, int duty_cycle)
{
    switch (pin)
    {
        case 1: // OC1A //Arduino Pin 9
        {
			DDRB |= (1 << DDB1);
            TCCR1A |= (1 << COM1A1) | (1 << WGM10);
            TCCR1B |= (1 << WGM12) | (1 << CS11);
            OCR1A = duty_cycle;
            break;
        }
        case 2: // OC1B //Arduino Pin 10
        {
			DDRB |= (1 << DDB2);
            TCCR1A |= (1 << COM1B1) | (1 << WGM10);
            TCCR1B |= (1 << WGM12) | (1 << CS11);
            OCR1B = duty_cycle;
            break;
        }
        case 3: // OC2A //Arduino Pin 11
        {
			DDRB |= (1 << DDB3);
            TCCR2A |= (1 << COM2A1) | (1 << WGM20) | (1 << WGM21);
            TCCR2B |= (1 << CS21);
            OCR2A = duty_cycle;
            break;
        }
        case 19:// OC2B  //Arduino Pin 3
        {
			DDRD |= (1 << DDD3);
            TCCR2A |= (1 << COM2B1) | (1 << WGM20) | (1 << WGM21);
            TCCR2B |= (1 << CS21);
            OCR2B = duty_cycle;
            break;
        }
        case 21:// OC0B //Arduino Pin 5
        {
			DDRD |= (1 << DDD5);
            TCCR0A |= (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
            TCCR0B |= (1 << CS01);
            OCR0B = duty_cycle;
            break;
        }
        case 22:// OC0A //Arduino Pin 6
        {
			DDRD |= (1 << DDD6);
            TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
            TCCR0B |= (1 << CS01);
            OCR0A = duty_cycle;
            break;
        }
    }
}

#ifdef __cplusplus
}
#endif