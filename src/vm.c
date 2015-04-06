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
 * Description: This file implements the virtual machine. 
 */
#include "../processors/atmega328.h"
#include "HAL.h"

typedef struct decoded_instruction
{
  uint8_t op;
  union {
    struct R {
      // op == 000000
      uint8_t rs, rt, rd, shamt, funct;
    };
    struct I {
      uint8_t rs, rt; 
      uint16_t immediate;
    };
    struct J {
      uint32_t address;
    };
  };
} decoded_instruction_t;


uint8_t VM_memory[VM_MEMORY_SZ];

/*
 * Central processing unit. It continuously fetches and executes
 * instructions.
 */
void vm_cpu()
{
  /* Register file. */
  uint32_t RF[32];

  uint32_t PC = 0;
  uint8_t halted = 0;


  while (!halted) {

    uint32_t instr = fetch(PC);
    uint8_t op = (instr >> 26) && 0x3F;

  
    switch (op) {
    case 0x0: { // 000000 => Register encoding.
      uint8_t rs = (instr >> 21)   && 0x1F;
      uint8_t rt = (instr >> 16)   && 0x1F;
      uint8_t rd = (instr >> 11)   && 0x1F;
      uint8_t shamt = (instr >> 6) && 0x1F;
      uint8_t funct = (instr >> 0) && 0x3F;
      
      switch (funct) {
		  case 0b100000: { // add	100000	ArithLog	$d = $s + $t
			RF[rd] = RF[rs] + RF[rt];
			break;
		  }
		  case 0b100001: { // addu	100001	ArithLog	$d = $s + $t
			RF[rd] = RF[rs] + RF[rt];
			break;
		  }
		  case 0b100100: { // and	100100	ArithLog	$d = $s & $t
			RF[rd] = RF[rs] & RF[rt];
			break;
		  }
		  case 0b011010: { // div     011010  DivMult lo = $s / $t; hi = $s % $t
			  
			  break;
		  }
		  case 0b011011: { //divu    011011  DivMult lo = $s / $t; hi = $s % $t
			  
			  break;
		  }
		  case 0b011000: { //mult    011000  DivMult hi:lo = $s * $t

			  break;
		  }


		  //case ...
		  // Other instructions...
      }
      break; // case 0x0
    }
    //case :
	
      
      uint8_t op = (instr >> 26) && 0x3F;
    }
  }

}
uint32_t fetch(uint32_t PC)
{
	return 0;
}





