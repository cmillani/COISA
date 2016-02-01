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

#include <stdutils.h>
	
uint8_t result = 1;
char temp;
uint8_t counter;
	
void strcpy(char dest[], char origin[])
{
	for(counter = 0; origin[counter] != '\0'; counter++)
	{
		dest[counter] = origin[counter];
	}
}

uint8_t strcmp(char one[], char two[])
{
	result = 0; //Starts as true (string.h strcmp like)
	counter = 0;
	do {
		result = !(one[counter] == two[counter]); //Compares the two strings and output the result to the variable (as 0 means equal, we need the NOT)
		counter++;
	} while (one[counter] != '\0' && two[counter] != '\0' && result == 0); //Breaks with the first \0 to avoid segfault or as soon as it`s not true anymore
	return result;
}


#ifdef __cplusplus
}
#endif