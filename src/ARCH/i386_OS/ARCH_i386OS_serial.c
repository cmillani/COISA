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
	
#include <stdio.h>
#include "ARCH_serial.h"

volatile unsigned char buff_in[20];
volatile uint8_t buff_in_pos = 0;
volatile unsigned char buff_out[20];
volatile uint8_t buff_out_pos = 0;

volatile uint8_t has_command = 0;

volatile uint8_t trash;
volatile uint32_t serial_timestamp = 0;


void send_byte(unsigned char byte)
{
	printf("%c", byte);
}
char read_byte(void)
{
	char c;
	scanf ("%c", &c);
	return c;
}

void print_pckg(char * str) {
	int i = 0;
	while (i < 20)
	{
		send_byte(str[i++]);
	}
}


void serial_configure(unsigned int baudrate)
{

}
void enable_commands(void) {
	
}
void printnum(int32_t number)
{
	printf("%d",number);
}
void print(char *str)
{
	printf("%s", str);
}
	
#ifdef __cplusplus
}
#endif