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

#include "HAL.h"
#if DEBUGING
#include <stdio.h>
#endif

/*Defined peripherals ids:
	Ultrasonic		0
	Serial			1
	Encoder			2
*/

uint8_t hal_call(uint32_t sensid)//Call to hardware I/O
{
	uint8_t retval = -1;
	switch (sensid)
	{
		case 0: { //Read Ultrasonic
#if DEBUGING
			printf("Hal read called\n");
#endif
		}
		default:
			break;
	}
	return retval;
}

#ifdef __cplusplus
}
#endif