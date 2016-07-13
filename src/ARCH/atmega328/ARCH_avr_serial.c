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
#include <avr/io.h>
#include <avr/interrupt.h>

volatile char rx_buff[BUFFER_SZ] = {0};
volatile uint8_t rx_buff_pos = 0;
// char tx_buff[2] = {0};

volatile uint8_t has_command = 0;
volatile char inBuffer[BUFFER_SZ+1] = {0};
volatile char outBuffer[BUFFER_SZ] = {0};

/*
	Buffer:
	2B:CommandID||18B:Body
	
*/

ISR(USART_RX_vect) {
	//Every command has 2 chars, which is enought for out TM :)
	//When this buffer is full, we copy it to save data and set a flag, so TM can handle it
	rx_buff[rx_buff_pos] = UDR0; //TODO: may have some sync problems, pack it later
	if (!has_command && ++rx_buff_pos == BUFFER_SZ) { //Buffer full, ack and then interprets
		has_command = 1;
		rx_buff_pos = 0;
		inBuffer[0] = rx_buff[0];
		inBuffer[1] = rx_buff[1];
		UCSR0B &= ~(1 << RXCIE0); // Stops receiving commands, so we can handle the received first
	}
}

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
	inBuffer[0] = '\0';
	UBRR0H = (16000000/16/baudrate -1 >> 8); //Configure baudrate generator
	UBRR0L = (16000000/16/baudrate -1); //Configure baudrate generator
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);// | (1 << TXCIE0); //TODO: Use TX interrupt too
	sei(); //Enables interruption
}

void enable_commands(void) {
	UCSR0B |= (1 << RXCIE0);
	sei();
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