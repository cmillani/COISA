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
	
#include "serial.h"
    
void serial_init(unsigned int baudrate)
{
	UBRR0H = (16000000/16/baudrate -1 >> 8);
	UBRR0L = (16000000/16/baudrate -1);
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
}
void serial_send(char a)
{
  while (!(UCSR0A & (1 << UDRE0))); // Wait until buffer is empty
  UDR0 = a;
}
char serial_read(void)
{
  while (!(UCSR0A & (1 << RXC0)));
  return UDR0;
}

#ifdef __cplusplus
}
#endif
