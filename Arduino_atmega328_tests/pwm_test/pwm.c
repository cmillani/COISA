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
	
#include "pwm.h"
    
void set_PWM(int pin, int duty_cycle)
{
  switch (pin)
  {
    case 1: // OC1A //Arduino Pin 9
    {
      TCCR1A |= (1 << COM1A1) | (1 << WGM10);
      TCCR1A |= (1 << WGM12) | (1 << CS11);
      OCR1A = duty_cycle;
      break;
    }
    case 2: // OC1B //Arduino Pin 10
    {
      TCCR1A |= (1 << COM1B1) | (1 << WGM10);
      TCCR1A |= (1 << WGM12) | (1 << CS11);
      OCR1B = duty_cycle;
      break;
    }
    case 3: // OC2A //Arduino Pin 11
    {
      TCCR2A |= (1 << COM2A1) | (1 << WGM20) | (1 << WGM21);
      TCCR2B |= (1 << CS21);
      OCR2A = duty_cycle;
      break;
    }
    case 19:// OC2B //Arduino Pin 3
    {
      TCCR2A |= (1 << COM2B1) | (1 << WGM20) | (1 << WGM21);
      TCCR2B |= (1 << CS21);
      OCR2B = duty_cycle;
      break;
    }
    case 21:// OC0B //Arduino Pin 5
    {
      TCCR0A |= (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
      TCCR0B |= (1 << CS01);
      OCR0B = duty_cycle;
      break;
    }
    case 22:// OC0A //Arduino Pin 6
    {
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
