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
#define BASE_POW 180
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
	
float pow_right = 0;
float pow_left = 0;
	
void setup_movement(void)
{
	serial_configure(9600);
	DDRC |= (1 << DDC4);
	DDRC |= (1 << DDC0);
	PORTC |= (1 << PC4);
	PORTC |= (1 << PC0);
	//a4 and a0 pc4 and pc0
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

void update_powers(void);

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

float Kp = 0.5;
float Ki = 0.15;
float Kd = 0.2;

float il = 0;
float ir = 0;
int target_r = 80;
int target_l = 80;

int last_r = 0;
int last_l = 0;
int now_r = 0;
int now_l = 0;
int last_time = 0;

int last_rpm_r = 0;
int last_rpm_l = 0;

float i_xdiff = 0;
float last_xdiff = 0;

void PID_ON(void)
{
	last_time = timer0_ovf_count;
}

void set_targetRPM_R(int rpm)
{
	target_r = rpm;
}
void set_targetRPM_L(int rpm)
{
	target_l = rpm;
}

void PID(void)
{
	now_r = read_encoder_counter(RIGHT);
	now_l = read_encoder_counter(LEFT);
	
	float xdiff = (now_r - now_l)*0.8 + last_xdiff * 0.2;
	i_xdiff += xdiff;
	float d_xdiff = xdiff - last_xdiff;
	
	int now_time = timer0_ovf_count;
	
	float rpm_r = (now_r-last_r)*23437.5/(now_time-last_time);
	float rpm_l = (now_l-last_l)*23437.5/(now_time-last_time);

	float filtered_r = 0.5*last_rpm_r + 0.5*rpm_r;
	float filtered_l = 0.5*last_rpm_l + 0.5*rpm_l;
	
	// if (now_r < 2 && now_l < 2)
// 	{
// 		last_r = now_r;
// 		last_l = now_l;
//
// 		last_time = now_time;
//
// 		last_rpm_l = rpm_r;
// 		last_rpm_r = rpm_l;
// 		last_xdiff = now_r - now_l;
// 		return;
// 	}
	
	// printnum(now_r);
	// print("\t");
	// printnum(now_time);
	// print("\n");
	// printnum(now_time);
	// printnum(now_time-last_time);
	// printnum(last_xdiff);
	// print("\t");
	// printnum(pow_left);
	// printnum(i_xdiff);
	// printnum((now_r-last_r)*23437.5);
	// printnum(now_l-last_l);
	// print("\t");
	// printnum(last_time);
	// printnum(pow_right);
	// printnum(xdiff);
	// print("\t");
	// printnum(filtered_l);
	// print("\t");
	// printnum(filtered_r);
	// printnum((now_l-last_l)*23437.5);
	// printnum(now_r-last_r);
	// print("\r\n");
	float pl = target_l - rpm_l;
	float pr = target_r - rpm_r;
	il += pl;
	ir += pr;
	float resl = Kp * pl + Ki * il + 2 * xdiff + 0.5 * i_xdiff;
	float resr = Kp * pr + 1.1*Ki * ir - 2 * xdiff - 0.5 * i_xdiff;
	
	pow_right = (int)resr;
	pow_left = (int)resl;
	
	if (pow_right > 255) pow_right = 255;
	else if (pow_right < -255) pow_right = -255;
	else if (filtered_r < 5 && target_r == 0) pow_right = 0;
	
	if (pow_left > 255) pow_left = 255;
	else if (pow_left < -255) pow_left = -255;
	else if (filtered_l < 5 && target_l == 0) pow_left = 0;
	
	update_powers();
	
	last_r = now_r;
	last_l = now_l;
	
	last_time = now_time;
	
	last_rpm_l = filtered_l;
	last_rpm_r = filtered_r;
	last_xdiff = xdiff;
}

void update_powers()
{
	if (pow_right > 0)
	{
		ahead_R();
	} 
	else if (pow_right < 0)
	{
		back_R();
	}
	else if (pow_right == 0)
	{
		stop_motor_R();
	} 
	
	if (pow_left >= 0)
	{
		ahead_L();
	}
	else if (pow_left < 0)
	{
		back_L();
	}
	else if (pow_left == 0)
	{
		stop_motor_L();
	}
}

#ifdef __cplusplus
}
#endif