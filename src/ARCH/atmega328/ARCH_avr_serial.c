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
	
#include "ARCH_serial.h"
#include <avr/io.h>

void send_byte(unsigned char byte)
{
	while (!(UCSR0A & (1 << UDRE0))); // Wait until buffer is empty (can send new data)
	UDR0 = byte;
}
char read_byte(void)
{
	while (!(UCSR0A & (1 << RXC0))); // Wait until there is something to read
	return UDR0;
}
void serial_configure(unsigned int baudrate)
{
	UBRR0H = (16000000/16/baudrate -1 >> 8); //Configure baudrate generator
	UBRR0L = (16000000/16/baudrate -1); //Configure baudrate generator
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
}
void printnum(uint32_t number)
{
	uint32_t temp = number;
	uint32_t max = 10;
	uint32_t counter = 0;
	do
	{
		temp /= 10;
		counter++;
	} while(temp > 0);
	for(temp = 0; temp < counter-1; temp++)
	{
		max *= 10;
	}
	for (; max > 1; max/=10)
	{
		send_byte((number%(max))/(max/10) + '0');
	}
}
void print(const char *str)
{
	int i = 0;
	while (str[i] != '/0')
	{
		send_byte(str[i]);
	}
}
	
#ifdef __cplusplus
}
#endif