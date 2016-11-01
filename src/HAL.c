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

#include <HAL.h>
#include "vm.h"
#include <stdutils.h>
#include <magnetometer.h>
#include <math.h>
#define PI (3.141592653589793)
	
#if PRINTING
#include <stdio.h>
#endif

/*Defined peripherals ids:
	See file on doc/CallsDefinition.txt
*/

uint8_t hal_call(uint32_t sensid, char identifier[])//Call to hardware I/O
{
	// print(identifier);
	// printnum(sensid);
	// print("<>");
	// printnum(RF[4]);
	// print("\n");
	uint8_t retval = 0;
	if (!strcmp(identifier,"US_S"))
	{
#if HAS_ULTRASONIC
		switch (sensid)
		{
			case 0: { //Read Ultrasonic
	#if PRINTING
				printf("(HAL)Read Ultra called\n");
	#endif // PRINTING
				retval = read_ultrassonic();
				// print("LEITURA:");
				// printnum(retval);
				// print("\n");
				break;
			}
			case 1: {
	#if PRINTING
				printf("(HAL)Config Ultra called\n");
	#endif // PRINTING
				configure_ultrassonic(RF[4]);
				break;
			}
			case 2: {
				init_ultrassonic();
				break;
			}
		}
#endif
	}
	else if (!strcmp(identifier,"LEDS"))
	{
#if HAS_LEDS
		switch (sensid)
		{
			case 0: //Led On
				ledon(RF[4]);
				break;
			case 1: //Led Off
				ledoff(RF[4]);
				break;
		}
#endif
	}
	else if (!strcmp(identifier,"ENCD"))
	{
#if HAS_ENCODER
		switch (sensid)
		{
			case 5 : {
	#if PRINTING
				printf("(HAL)Read Encoder Count called\n");
	#endif // PRINTING	
				// read_encoder_counter(0);
				break;
			}
			case 6 : {
	#if PRINTING
				printf("(HAL)Read Encoder Time called\n");
	#endif // PRINTING	
				break;
			}
			
			case 7 : {
				encd_threshold = RF[4]; //Sets threshold for the encoder
			}
			case 8 : {
				encd_movdone = RF[4];
			}
		}
#endif
	}
	else if (!strcmp(identifier,"RXTX"))
	{
#if HAS_SERIAL 
		switch (sensid)
		{
			case 10: {
	#if PRINTING
				printf("(HAL)Send Byte called\n");
	#endif // PRINTING	
				send_byte(RF[4]);
				break;
			}
			case 11: {
	#if PRINTING
				printf("(HAL)Read Byte called\n");
	#endif // PRINTING
				// RF[2] = read_byte();
				break;	
			}
			case 12: {
	#if PRINTING
				printf("(HAL)Configure serial called\n");
	#endif // PRINTING	
				serial_configure(RF[4]); //TODO: Allow user to enable and disable interruptions later
				break;
			}
			case 13: {
	#if PRINTING
				printf("(HAL)Print number called\n");
	#endif // PRINTING	
				printnum(RF[4]); 
				break;
			}
			case 14: {
	#if PRINTING
				printf("(HAL)Print string called\n");
	#endif // PRINTING	
				print((char *)&VM_memory[RF[4]]);
				break;
			}
		}
#endif
	}
	else if (!strcmp(identifier,"MOVM"))
	{
#if HAS_STEPPER
		switch (sensid)
		{
			case 18: {
	#if PRINTING
				printf("(HAL)Mov. Setup called\n");
	#endif		
				init_stepper();
				break;
			}
			case 21: { //Forward
				uint32_t timestamp_steps = 0;
				int x = 2000;
				int steps = 0;
				while(steps < x) {
					uint32_t now = timer_get_ticks();
					if (now - timestamp_steps > 1000) {
						forward_stepper(LEFT_STEPPER);
						forward_stepper(RIGHT_STEPPER);
						timestamp_steps = now;
						steps++;
						// print("-\n");
					}
				}
				stop_stepper(LEFT_STEPPER);
				stop_stepper(RIGHT_STEPPER);
				break;
			}
			case 22: { //Left
				uint32_t timestamp_steps = 0;
				int x = 2200;
				int steps = 0;
				while(steps < x) {
					uint32_t now = timer_get_ticks();
					if (now - timestamp_steps > 1000) {
						backward_stepper(LEFT_STEPPER);
						forward_stepper(RIGHT_STEPPER);
						timestamp_steps = now;
						steps++;
						// print("-\n");
					}
				}
				stop_stepper(LEFT_STEPPER);
				stop_stepper(RIGHT_STEPPER);
				break;
			}
			case 23: { //Right
				uint32_t timestamp_steps = 0;
				int x = 2200;
				int steps = 0;
				while(steps < x) {
					uint32_t now = timer_get_ticks();
					if (now - timestamp_steps > 1000) {
						forward_stepper(LEFT_STEPPER);
						backward_stepper(RIGHT_STEPPER);
						timestamp_steps = now;
						steps++;
						// print("-\n");
					}
				}
				stop_stepper(LEFT_STEPPER);
				stop_stepper(RIGHT_STEPPER);
				break;
			}
			case 24: { //Stop
				stop_stepper(LEFT_STEPPER);
				stop_stepper(LEFT_STEPPER);
				break;
			}
		}
#elif HAS_MOTORS
		switch (sensid)
		{
			case 15: {
	#if PRINTING
				printf("(HAL)Ahead called\n");
	#endif		
				// ahead();
				break;
			}
			case 16: { 
	#if PRINTING
				printf("(HAL)Right called\n");
	#endif		
				// turn_right();
				break;
			}
			case 17: {
	#if PRINTING
				printf("(HAL)Left called\n");
	#endif		
				// turn_left();
				break;
			}
			case 18: {
	#if PRINTING
				printf("(HAL)Mov. Setup called\n");
	#endif		
				setup_movement();
				break;
			}
			case 20: {
	#if PRINTING
				printf("(HAL)PWM called\n");
	#endif		
				break;
			}
			case 21: { //Forward
				reset_variables();
				set_targetRPM_L(110);
				set_targetRPM_R(110);
				isMoving = 1;
				isMoving_l = 1;
				isMoving_r = 1;
				reset_counter(RIGHT);
				reset_counter(LEFT);
				// ahead_L(218);
				// ahead_R(228);
				break;
			}
			case 22: { //Left
				reset_variables();
				set_targetRPM_L(110);
				set_targetRPM_R(110);
				isMoving = 1;
				isMoving_l = 1;
				isMoving_r = 1;
				set_target_tick_L(-18);
				set_target_tick_R(18);
				reset_counter(RIGHT);
				reset_counter(LEFT);
				// reset_variables();
				// set_targetRPM_L(-80);
				// set_targetRPM_R(80);
				// reset_counter(RIGHT);
				// reset_counter(LEFT);
				// mag_read();
				// desired_theta += 90;//(atan2(mag_x,mag_y) * 180 / PI) + 90;
				// isTurning = 1;
				// back_L(235);
				// ahead_R(218);
				break;
			}
			case 23: { //Right
				reset_variables();
				set_targetRPM_L(110);
				set_targetRPM_R(110);
				isMoving = 1;
				isMoving_l = 1;
				isMoving_r = 1;
				set_target_tick_L(18);
				set_target_tick_R(-18);
				reset_counter(RIGHT);
				reset_counter(LEFT);
				// reset_variables();
				// set_targetRPM_L(80);
				// set_targetRPM_R(-80);
				// reset_counter(RIGHT);
				// reset_counter(LEFT);
				// mag_read();
				// desired_theta -= 90;// (atan2(mag_x,mag_y) * 180 / PI) - 90;
				// isTurning = 1;
				// ahead_L(235);
				// back_R(218);
				break;
			}
			case 24: { //Stop
				reset_variables();
				// set_targetRPM_L(0);
				// set_targetRPM_R(0);
				reset_counter(RIGHT);
				reset_counter(LEFT);
				ahead_R(0);
				ahead_L(0);
				break;
			}
		}
#endif
	}
#if HAS_BUTTON
	else if(!strcmp(identifier,"BTOG"))
	{
		// print("BUT\n");
		init_button(RF[4], RF[5]);
	}
#endif
	else
	{
#if PRINTING
			printf("(HAL) error - Unknown Hal Call number\n");
#endif	
	}
	return retval;
}

#ifdef __cplusplus
}
#endif