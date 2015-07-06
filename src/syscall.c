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

/*
 * Description: This file implements the available syscalls.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "syscall.h"
#include "HAL.h"
	
#if PRINTING
#include <stdio.h>
#endif
 
uint8_t syscall(uint8_t trap_code)
{
	switch (trap_code)
	{
		case 10: { //Exit
			return 1; //The vm cpu should stop
			break;
		}
		case 11: { //Stack alloc
			RF[29] = VM_MEMORY_SZ; //Aloca pilha para dado microcontrolador -> pilha vazia, apontando para o fim, tentativa de store sem alocar causara erros
			RF[30] = RF[29]; //FP = SP
#if PRINTING
			printf("Stack initialized\n");
#endif
			break;
		}
		case 12: { //Hall Call
			RF[2] = hal_call(RF[3]);
		}
		
		// TODO Insert hall 
		
		default: {
			break;
		}
	}
	return 0;
}
    
#ifdef __cplusplus
}
#endif