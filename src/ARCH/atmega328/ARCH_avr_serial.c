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
#include <stdint.h>
#include <timer.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define TIMEOUT 1000000

volatile unsigned char buff_in[20];
volatile uint8_t buff_in_pos = 0;
volatile unsigned char buff_out[20];
volatile uint8_t buff_out_pos = 0;

volatile uint8_t has_command = 0;
volatile uint8_t timedOut = 0;

volatile uint8_t trash;
volatile uint32_t serial_timestamp = 0;

ISR(USART_RX_vect) {
	uint32_t newtimer = timer_get_ticks();
	if (has_command) {
		trash = UDR0;
	} else {
		if (newtimer - serial_timestamp > TIMEOUT) {
			buff_in_pos = 0;
			timedOut = 1;
		}
		serial_timestamp = newtimer;
		buff_in[buff_in_pos++] = UDR0;
		if (buff_in_pos >= 20) { //Buffer full!
			has_command = 1;
			buff_in_pos = 0;
		}
	}
}

void send_byte(unsigned char byte)
{
	while (!(UCSR0A & (1 << UDRE0))); // Wait until buffer is empty (can send new data)
	UDR0 = byte;
}
// char read_byte(void)
// {
// 	while (!(UCSR0A & (1 << RXC0))); // Wait until there is something to read
// 	return UDR0;
// }

void serial_configure(unsigned int baudrate)
{
	UBRR0H = (16000000/16/baudrate -1 >> 8); //Configure baudrate generator
	UBRR0L = (16000000/16/baudrate -1); //Configure baudrate generator
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);// | (1 << TXCIE0); //TODO: Use TX interrupt too
	sei(); //Enables interruption
}

void printnum(int32_t number)
{
	if (number < 0) 
	{
		number = -number;
		send_byte('-');
	}
	int32_t temp = number;
	int32_t max = 10;
	int32_t counter = 0;
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

void print_pckg(char * str) {
	int i = 0;
	while (i < 20)
	{
		send_byte(str[i++]);
	}
}

void print(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		send_byte(str[i++]);
	}
}
	
#ifdef __cplusplus
}
#endif