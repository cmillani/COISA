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
uint8_t stdu_counter;
	
void strcpy(char dest[], char origin[])
{
	for(stdu_counter = 0; origin[stdu_counter] != '\0'; stdu_counter++)
	{
		dest[stdu_counter] = origin[stdu_counter];
	}
}

uint8_t strcmp(char one[], char two[])
{
	result = 0; //Starts as true (string.h strcmp like)
	stdu_counter = -1;
	do {
		stdu_counter++;
		result = !(one[stdu_counter] == two[stdu_counter]); //Compares the two strings and output the result to the variable (as 0 means equal, we need the NOT)
	} while (one[stdu_counter] != '\0' && two[stdu_counter] != '\0' && result == 0); //Breaks with the first '\0' to avoid segfault or as soon as it`s not true anymore
	return result;
}

uint8_t strcmpsz(char one[], char two[], uint8_t sz)
{
	result = 0; //Starts as true (string.h strcmp like)
	stdu_counter = -1;
	do {
		stdu_counter++;
		result = !(one[stdu_counter] == two[stdu_counter]); //Compares the two strings and output the result to the variable (as 0 means equal, we need the NOT)
	} while (one[stdu_counter] != '\0' && two[stdu_counter] != '\0' && result == 0 && stdu_counter < sz-1); //Breaks with the first '\0' to avoid segfault or as soon as it`s not true anymore or as soon as size match
	return result;
}


#ifdef __cplusplus
}
#endif