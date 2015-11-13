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
	
#include <CONFIG_timer.h>
#include <config.h>	

int threshold = 1;
volatile int counter = 0;
	
uint16_t best_PS(void)
{
	uint32_t ideal = (F_CPU/F_INT);
	uint32_t real = 1;
	while (ideal > 1)
	{
		real = real << 1;
		ideal = ideal >> 1; 
		if (F_CPU%(real*F_INT) != 0 || real >= MAX_PS) 
		{
			real = real >> 1;
			break;
		}
	}
	return real;
}
	
#ifdef __cplusplus
}
#endif