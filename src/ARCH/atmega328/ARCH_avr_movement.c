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

#include <avr/interrupt.h>
#include <avr/io.h>
#include <ARCH_serial.h>
#include <ARCH_encoder.h>
#include <ARCH_PWM.h>
#include <ARCH_movement.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
	
#define MOVE_DURATION 30
#define KP 0.005
#define KI 0.001
#define BASE_POW 210
#define MIN_POW 160

#define HOLE_COUNT 20.0
#define DIAMETER 69.6
#define WHEEL_WIDTH 26.3
#define BETWEEN_WHEELS_DIST 111.6

#define ONE_WHEEL_TURN (DIAMETER*M_PI)
#define BETWEEN_HOLES (ONE_WHEEL_TURN/HOLE_COUNT)
#define ONE_TURN ((BETWEEN_WHEELS_DIST+WHEEL_WIDTH)*M_PI)
// #define QUARTER_TURN (((ONE_TURN/4)/(BETWEEN_HOLES)) + 1)
#define QUARTER_TURN 15

#define RIG0 22 //6 on arduino
#define RIG1 1 //09 on arduino
#define LEF0 2 //10 on arduino
#define LEF1 3 //11 on arduino
	
float pow_right = BASE_POW;
float pow_left = BASE_POW;
	
void setup_movement(void)
{
	serial_configure(9600);
	set_PWM(LEF1, 0);
	set_PWM(LEF0, 0);
	set_PWM(RIG0, 0);
	set_PWM(RIG1, 0);
	start_encoder();
}
void ahead(void)
{
	// printnum(read_encoder_counter(RIGHT));
	// print("\n");
	pow_left = BASE_POW;
	pow_right = BASE_POW;
	reset_counter(LEFT);
	reset_counter(RIGHT);
	// changed = 0;
	while(read_encoder_counter(RIGHT) < MOVE_DURATION && read_encoder_counter(LEFT) < MOVE_DURATION)
	{
		ahead_R();
		ahead_L();
		// if (changed)
// 		{
// 			changed = 0;
// 			if (read_encoder_counter(RIGHT) > read_encoder_counter(LEFT))
// 			{
// 				if (pow_right > MIN_POW) pow_right-= 1;
// 				if (pow_left < 255) pow_left+= 1;
// 			}
// 			else if (read_encoder_counter(RIGHT) < read_encoder_counter(LEFT))
// 			{
// 				if (pow_right < 255) pow_right+= 1;
// 				if (pow_left > MIN_POW) pow_left-= 1;
// 			}
// 		}
		// printnum(read_encoder_counter(RIGHT));
		// print("\n");
		control();
	}
	// if (read_encoder_counter(RIGHT) < MOVE_DURATION )
// 	{
// 		stop_motor_L();
// 		while (read_encoder_counter(RIGHT) < MOVE_DURATION )
// 		{
// 			ahead_R();
// 		}
// 		stop_motor_R();
// 	}
// 	else if (read_encoder_counter(LEFT) < MOVE_DURATION )
// 	{
// 		stop_motor_R();
// 		while (read_encoder_counter(LEFT) < MOVE_DURATION )
// 		{
// 			ahead_L();
// 		}
// 		stop_motor_L();
// 	}
	stop_motor_L();
	stop_motor_R();
	pow_right = BASE_POW;
	pow_left = BASE_POW;
}
void turn_left(void)
{
	pow_left = BASE_POW;
	pow_right = BASE_POW;
	reset_counter(LEFT);
	reset_counter(RIGHT);
	while(read_encoder_counter(RIGHT) < (int)(QUARTER_TURN+0.5) && read_encoder_counter(LEFT) < (int)(QUARTER_TURN-0.5))
	{
		ahead_R();
		back_L();
		if (read_encoder_counter(RIGHT) > read_encoder_counter(LEFT))
		{
			if (pow_right > MIN_POW) pow_right--;
			if (pow_left < 255) pow_left++;
		}
		else if (read_encoder_counter(RIGHT) < read_encoder_counter(LEFT))
		{
			if (pow_right < 255) pow_right++;
			if (pow_left > MIN_POW) pow_left--;
		}
		// control();
	}
	// if (read_encoder_counter(RIGHT) < (int)(QUARTER_TURN+0.5) )
// 	{
// 		stop_motor_L();
// 		while (read_encoder_counter(RIGHT) < (int)(QUARTER_TURN+0.5) )
// 		{
// 			ahead_R();
// 		}
// 		stop_motor_R();
// 	}
// 	else if (read_encoder_counter(LEFT) < (int)(QUARTER_TURN-0.5) )
// 	{
// 		stop_motor_R();
// 		while (read_encoder_counter(LEFT) < (int)(QUARTER_TURN-0.5) )
// 		{
// 			back_L();
// 		}
// 		stop_motor_L();
// 	}
	stop_motor_L();
	stop_motor_R();
	pow_right = BASE_POW;
	pow_left = BASE_POW;
}
void turn_right(void)
{
	pow_left = BASE_POW;
	pow_right = BASE_POW;
	reset_counter(LEFT);
	reset_counter(RIGHT);
	while(read_encoder_counter(RIGHT) < (int)(QUARTER_TURN-0.5) && read_encoder_counter(LEFT) < (int)(QUARTER_TURN+0.5))
	{
		back_R();
		ahead_L();
		// if (read_encoder_counter(RIGHT) > read_encoder_counter(LEFT))
// 		{
// 			if (pow_right > MIN_POW) pow_right--;
// 			if (pow_left < 255) pow_left++;
// 		}
// 		else if (read_encoder_counter(RIGHT) < read_encoder_counter(LEFT))
// 		{
// 			if (pow_right < 255) pow_right++;
// 			if (pow_left > MIN_POW) pow_left--;
// 		}
		control();
	}
	// if (read_encoder_counter(RIGHT) < (int)(QUARTER_TURN-0.5) )
// 	{
// 		stop_motor_L();
// 		while (read_encoder_counter(RIGHT) < (int)(QUARTER_TURN-0.5) )
// 		{
// 			back_R();
// 		}
// 		stop_motor_R();
// 	}
// 	else if (read_encoder_counter(LEFT) < (int)(QUARTER_TURN+0.5) )
// 	{
// 		stop_motor_R();
// 		while (read_encoder_counter(LEFT) < (int)(QUARTER_TURN+0.5) )
// 		{
// 			ahead_L();
// 		}
// 		stop_motor_L();
// 	}
	stop_motor_L();
	stop_motor_R();
	pow_right = BASE_POW;
	pow_left = BASE_POW;
}
/**************************************************************/

/**************************************************************/
void ahead_L(void)
{
	set_PWM(LEF0, (int)pow_left);
	set_PWM(LEF1, 0);
}
void ahead_R(void)
{
	set_PWM(RIG0, (int)pow_right);
	set_PWM(RIG1, 0);
}
void back_R(void)
{
	set_PWM(RIG0, 0);
	set_PWM(RIG1, (int)pow_right);
}
void back_L(void)
{
	set_PWM(LEF0, 0);
	set_PWM(LEF1, (int)pow_left);
}
void stop_motor_L(void)//Turn off left motor
{
	set_PWM(LEF0, 0);
	set_PWM(LEF1, 0);
}
void stop_motor_R(void)//Turn off right motor 
{
	set_PWM(RIG0, 0);
	set_PWM(RIG1, 0);
}
void control(void)
{
	if (read_encoder_time(LEFT) == 0 || read_encoder_time(RIGHT) == 0) return;
	static int32_t I = 0;
	int32_t P = 0;
	// printnum(read_encoder_time(LEFT));
	// print(">>");
	// printnum(read_encoder_time(RIGHT));
	// print(">>");
	int32_t diff = (read_encoder_time(LEFT) - read_encoder_time(RIGHT));
	
	// printnum(diff);
	// print("--");
	I += diff * KI;
	P = diff * KP;
	// printnum(diff<0?-diff:diff);
	// print("\n");
	pow_right = ((uint16_t)pow_right + I + P) > 255? 255:(pow_right + I + P) < MIN_POW? MIN_POW: (pow_right + I + P);
	pow_left = ((uint16_t)pow_right - (I + P)) > 255? 255:(pow_right - (I + P)) < MIN_POW? MIN_POW: (pow_right - (I + P));
	
	// printnum(I);
// 	print("--");
// 	printnum(P);
// 	print("--");
// 	printnum(read_encoder_time(RIGHT));
// 	print("-");
// 	printnum(read_encoder_time(LEFT));
// 	print("-");
// 	printnum(pow_right);
// 	print(" ");
// 	printnum(pow_left);
// 	print("\n");
}

#ifdef __cplusplus
}
#endif