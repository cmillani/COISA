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
#include "ultrasonic.h"
    
#define CM_CONVERSION 29*4
#define IN_CONVERSION 74*4
	
uint8_t conversion_factor = CM_CONVERSION; //Default is CM
uint8_t us_threshold = 0;
uint8_t is_close = 0;

void configure_ultrassonic(uint8_t mode) //Changes de conversion_factor so US returns the distance in the desired Unit System
{
	if(mode == CM) conversion_factor = CM_CONVERSION;
	else if (mode == IN) conversion_factor = IN_CONVERSION;
}

#ifdef __cplusplus
}
#endif