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

#include <TM.h>
#include <HAL.h>
#include <EH.h>
#include <vm.h>
#include <stdutils.h>
#include <inttypes.h>
#include <i2c.h>
#include <magnetometer.h>
#include <math.h>
#include <IMU.h>
#include <stepper.h>
#define PI (3.141592653589793)

uint32_t tm_counter = 0;
uint16_t tot_size = 0;

void idle(void);
void receiving_sz(void);
void receiving_x(void);
void executing(void);
void reseting(void);
void moving(void);
void breaking(void);
	
void (*state)(void);

void idle(void) {
	//TODO: should sleep here :)
}

// uint8_t pckg_count = 0;
uint16_t bytes_in = 0;
void receiving_sz(void) {

	tot_size = (uint16_t)buff_in[19] | ((uint16_t)buff_in[18] << 8);

	state = idle;
	// printnum(tot_size);
	// print("\n");
	bytes_in = 0;
	print_pckg("OK-RD\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
}

void receiving_x(void) {
	
	// for (i = 0; i < tot_size; i++) {
// 		VM_memory[i] = read_byte();
// 		if ((i+1)%20 == 0) send_byte('k');
// 	}
// 	if (tot_size%20 != 0) send_byte('k');
	
	for (bytes_in; bytes_in < tot_size; bytes_in++) {
		// printnum(buff_in[bytes_in%18 + 2]);
		// print("-");
		VM_memory[bytes_in] = buff_in[bytes_in%18 + 2];
		if (bytes_in%18 == 17) {
			bytes_in++;
			break;
		}
	}
	// printnum(bytes_in);
	//print("\n");
	print_pckg("OK-PK\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
	
	if (bytes_in == tot_size) {
		vm_init(0);
		state = executing;
	} else {
		state = idle;
	}
}

void executing(void) {
	uint8_t res = vm_cpu();
	if (res == 1) state = idle;
	else if (res == 2) state = moving;
}

void moving(void) {
#if HAS_MOTORS
	if (isTurning) return;
	// else if (isMoving && read_encoder_counter(RIGHT) >= encd_movdone){
	// 	ahead_R(0);
	// 	ahead_L(0);
	// 	set_targetRPM_R(0);
	// 	set_targetRPM_R(0);
	// 	isMoving = 0;
	// 	vm_release();
	// 	state = executing;
	// }
	else if (isMoving) return;
	else {
		// print("MOV END\n");
		vm_release();
		state = breaking;
	}
#else
	state = breaking;
#endif
}

uint16_t breaking_count = 0;
void breaking(void) {
	if (breaking_count > 5) {
		// print("NEEXT\n");
		breaking_count = 0;
		state = executing;
	};
}

void reseting(void) {
	eh_init();
	init_timer();
#if HAS_SERIAL
	serial_configure(9600);
#endif 
#if HAS_MOTORS
	setup_movement();
#endif
#if HAS_LEDS
	ledoff(1);
	ledoff(2);
#endif
#if HAS_ENCODER
	start_encoder();
#endif
	uint16_t i;
	for (i = 0; i < VM_MEMORY_SZ; i++) {
		VM_memory[i] = 0;
	}
	state = idle;
}

void parse_Command(volatile unsigned char * command) {
	has_command = 0;
	if (!strcmpsz((char *)command,"RD", 2)) {
		// print_pckg("RD-OK\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"); //20 bytes - TODO: improve
		state = receiving_sz;
	} else if (!strcmpsz((char *)command,"RS", 2)) {
		print_pckg("RS-OK\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
		state = reseting;
	// } else if (!strcmpsz((char *)command,"SZ", 2)) {
		// state = receiving_sz;
	} else if (!strcmpsz((char *)command,"PK", 2)) {
		state = receiving_x;
	} else {
		send_byte('-');
		send_byte(command[0]);
		send_byte('-');
		send_byte(command[1]);
		send_byte('-');
		print_pckg("\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
	}
}

void tm_init(void) {
/*COISA's Initialization*/
/*************************/
	eh_init();
	init_timer();
/*************************/
#if HAS_SERIAL
	serial_configure(9600);
#endif
/*************************/
#if HAS_MOTORS
	setup_movement();
#endif
/*************************/
#if HAS_ENCODER
	start_encoder();
#endif
/*************************/
#if HAS_ULTRASONIC
	init_ultrassonic();
#endif
/*************************/
#if HAS_STEPPER
	init_stepper();
#endif
/*************************/
	print("Will Init\n");
	// i2c_init();
	// mag_init();
	
	// uint32_t timestamp = 0;

	/*Everything initialized*/
	
	/*Sets initial State*/
	state = idle;
	// while(1) {
// 		uint32_t now = timer_get_ticks();
// 		if (now - timestamp > 1000) {
// 			forward_stepper(0);
// 			timestamp = now;
// 			// print("-\n");
// 		}
// 	}
	/*Coisa VM cpu, HAL, EH and TM loop*/
    while(1)
    {
#if HAS_MOTORS
		if (isMoving && timer_get_ticks() - timestamp > 30000) {
			if (isMoving_r) {
				tick_PID_r();
			}
			if (isMoving_l) {
				tick_PID_l();
			}
			if (!isMoving_r && !isMoving_l) {
				isMoving = 0;
			}
		}
		if (isTurning && timer_get_ticks() - timestamp > 30000) {
			theta_control();
			timestamp = timer_get_ticks();
		}
#endif
		if (has_command) {
			parse_Command(buff_in);
		}
		if(timer_flag)
		{	
			if (state == breaking) {
				breaking_count++;
			}
			tm_counter++;
			timed_polling();
			timer_flag = 0;
		#if HAS_MOTORS
			if (isTurning) {
				theta_control();
			}
			else if (tm_counter >= 6 && isMoving_l && isMoving_r) //Every 4 timer interruptions, should check for PID controlling
			{
				PID();
				tm_counter = 0;
			}
		#endif
			if (state == idle) //Doesn't interrupts other functions - All funcs must be non blocking
			{
				if (consume_event()) state = executing; //TODO: see on consume_event: problem with more than 1 handler
			}
		}
		state();
		
	}
}
	
#ifdef __cplusplus
}
#endif
	