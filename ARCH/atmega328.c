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
/*Implementation for an atmega328 based device*/

#ifdef __cplusplus
extern "C" {
#endif

#include "atmega328.h"
#include "../src/HAL.h"

void pinState(uint8_t pin_number, uint8_t state)
{
	
}

void pinMode(uint8_t pin_number, uint8_t mode)
{
	
}

void pinRead(uint8_t pin_number)
{
	
}

uint8_t read_ultrassonic(void)
{
	uint8_t microsecs = 0;
	
	//TODO read distance!
	
	return (uint8_t)(microsecs/conversion_factor);
};

#ifdef __cplusplus
}
#endif