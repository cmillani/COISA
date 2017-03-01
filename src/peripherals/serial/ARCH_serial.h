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
	
#ifndef ARCH_SERIAL	
#define ARCH_SERIAL
#include <stdint.h>
	
extern volatile uint8_t has_command;
extern volatile uint8_t receiving;
extern volatile uint32_t serial_timestamp;
extern volatile uint8_t buff_in_pos;

extern volatile unsigned char buff_in[20];
extern volatile unsigned char buff_out[20];

void send_byte(unsigned char byte);
// char read_byte(void);
void serial_configure(unsigned int ubrr); //Allow user to enable and disable interruptions later
void printnum(int32_t number);
void print(char *str);
void print_pckg(char *str);
void serial_timeout(void);

#endif //ARCH_SERIAL
	
#ifdef __cplusplus
}
#endif