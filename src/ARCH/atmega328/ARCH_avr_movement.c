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
#include <magnetometer.h>
#define PI (3.141592653589793)
	
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
int target_r = 0;
int target_l = 0;
	
void setup_movement(void)
{
	DDRC |= (1 << DDC4);
	DDRC |= (1 << DDC0);
	PORTC |= (1 << PC2);
	PORTC |= (1 << PC0);
	//a4 and a0 pc2 and pc0
	set_PWM(LEF1, 0);
	set_PWM(LEF0, 0);
	set_PWM(RIG0, 0);
	set_PWM(RIG1, 0);
	
	target_r = 0;
	target_l = 0;
	
	start_encoder();
	// mag_read();
	// desired_theta = atan2(mag_x,mag_y) * 180 / PI;
}
/**************************************************************/

/**************************************************************/
void ahead_L(int power)
{
	set_PWM(LEF0, power);
	set_PWM(LEF1, 0);
}
void ahead_R(int power)
{
	set_PWM(RIG0, power);
	set_PWM(RIG1, 0);
}
void back_R(int power)
{
	set_PWM(RIG0, 0);
	set_PWM(RIG1, power);
}
void back_L(int power)
{
	set_PWM(LEF0, 0);
	set_PWM(LEF1, power);
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

extern int desired_theta = 0;
int32_t ac_theta = 0;
int last_err_theta = 0;

void theta_control(void) {
	mag_read();
	if (desired_theta > 180) {
		desired_theta -= 360;
	} else if (desired_theta < -179) {
		desired_theta += 360;
	}
	
	int theta = (atan2(mag_x,mag_y) * 180 / PI);
	int error = desired_theta - theta;
	
	if (error > 180 ) {
		error -= 360;
	} else if (error < -179) {
		error += 360;
	}
	
	ac_theta += error;
	if (ac_theta > 120) ac_theta = 120;
	else if (ac_theta < -120) ac_theta = -120;
	
	int newPow = int(error * 4.25 + ac_theta * 0.5 + (error - last_err_theta) * 2);
	// int newPow = int(ac_theta * 2.0);
	newPow = newPow > 255? 255:(newPow < -255? -255:newPow);
	
	
	printnum(theta);
	print("\t");
	printnum(desired_theta);
	print("\t");
	printnum(error);
	print("\t");
	printnum(newPow);
	print("\t");
	printnum(ac_theta);
	print("\n");
	
	
	return;
	if (newPow > 0)
	{
		ahead_L(newPow);
		back_R(newPow);
	} 
	else if (newPow < 0)
	{
		back_L(-newPow);
		ahead_R(-newPow);
	} else {
		stop_motor_L();
		stop_motor_R();
	}
	
	last_err_theta = error;
}

int tick_l = 0;
int desired_tick_l = 20;
long int ac_err_l = 0;
int last_err_l = 0;

void tick_PID_l(void) {
	tick_l = read_encoder_counter(LEFT);
	int error = desired_tick_l - tick_l;
	ac_err_l += error;
	
	if (ac_err_l >= 1300) ac_err_l -= error;
	//kp = 7.5 ou 10
	//ki = 
	int newPow = error * 4.5  + ac_err_l * 0.02 + (error - last_err_l) * 2.0;
	newPow *= (40/desired_tick_l);
	// print("\t");
	// printnum(ac_err);
	// print("\n");
	

	
	newPow = newPow > 255? 255:(newPow < -255? -255:newPow);
	//
	if (desired_tick_l <= tick_l) {
		newPow = 0;
		// print("HERE\n");
	}
	
	if (newPow > 0)
	{
		ahead_L(newPow);
	} 
	else if (newPow < 0)
	{
		back_L(-newPow);
	} else {
		stop_motor_L();
	}
	last_err_l = error;
}


int tick_r = 0;
int desired_tick_r = 20;
long int ac_err_r = 0;
int last_err_r = 0;

void tick_PID_r(void) {
	// P 40 ticks 4.5, 0.02 e 2
	tick_r = read_encoder_counter(RIGHT);
	int error = desired_tick_r - tick_r;
	ac_err_r += error;
	
	if (ac_err_r >= 1300) ac_err_r -= error;
	//kp = 7.5 ou 10
	//ki = 
	int newPow = error * 4.5 + ac_err_r * 0.02 + (error - last_err_r) * 2.0;
	newPow *= newPow *= (40/desired_tick_r);
	// print("\t");
	// printnum(ac_err);
	// print("\n");
	
	
	newPow = newPow > 255? 255:(newPow < -255? -255:newPow);
	//
	if (desired_tick_r <= tick_r) {
		newPow = 0;
		// print("HERE\n");
	}
	
	if (newPow > 0)
	{
		ahead_R(newPow);
	} 
	else if (newPow < 0)
	{
		back_R(-newPow);
	} else {
		stop_motor_R();
	}
	last_err_r = error;
}

float KpL = 1.0;
float KiL = 0.35;
float KdL = 0.8;

float KpR = 1.1;
float KiR = 0.37;
float KdR = 0.82;

float KpT = 0.0;
float KiT = 0.0;
float KdT = 0.0;

float il = 0;
float ir = 0;

float last_pr = 0;
float last_pl = 0;

int last_r = 0;
int last_l = 0;
int now_r = 0;
int now_l = 0;
int last_time = 0;

float last_rpm_r = 0;
float last_rpm_l = 0;

float i_xdiff = 0;
float last_xdiff = 0;

float resr = 0;
float resl = 0;

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
	
	float xdiff = (now_r*(target_l) - now_l*(target_r))*0.8 + last_xdiff * 0.2;
	i_xdiff += xdiff;
	float d_xdiff = xdiff - last_xdiff;
	//Ver relação entre rpms pra definir relação entre ticks e fazer essa conta aqui de cima direito
	int now_time = timer0_ovf_count;
	
	float rpm_r = 0;
	float rpm_l = 0;
	if (now_time != last_time)
	{
		rpm_r = (now_r-last_r)*23437.5/(now_time-last_time);
		if (resr < 0) rpm_r *= -1;
		rpm_l = (now_l-last_l)*23437.5/(now_time-last_time);
		if (resl < 0) rpm_l *= -1;
	}

	float filtered_r = 0.5*last_rpm_r + 0.5*rpm_r;
	float filtered_l = 0.5*last_rpm_l + 0.5*rpm_l;
	
	float pl = target_l - filtered_l;
	float pr = target_r - filtered_r;
	il += pl;
	ir += pr;
	float dr = pr - last_pl;
	float dl = pl - last_pr;
	
	resl = (KpL * pl + KiL * il + KdL * dl) + (KpT * xdiff + KiT * i_xdiff);
	resr = (KpR * pr + KiR * ir + KdR * dr) - (KpT * xdiff + KiT * i_xdiff);
	
	// printnum(KpL * pl);
	// print("\t");
	// printnum(KiL * il);
	// print("\t");
	// printnum(KdL * dl);
	// print("\t");
	// printnum(resl);
	// print("\t");
	// printnum(filtered_l);
	// print("\r\n");
	// printnum(now_r);
	// print("\t");
	// printnum(now_l);
	// print("\r\n");
	
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
	last_pr = pr;
	last_pl = pl;
	
	last_time = now_time;
	
	last_rpm_l = filtered_l;
	last_rpm_r = filtered_r;
	last_xdiff = xdiff;
	
	il += 0;
	ir += 0;
}

void reset_variables() {
	
	reset_counter(RIGHT);
	reset_counter(LEFT);
	
	pow_right = 0;
	pow_left = 0;
	
	last_rpm_l = 0;
	last_rpm_r = 0;
	
	last_xdiff = 0;
	last_r = 0;
	last_l = 0;
	last_pr = 0;
	last_pl = 0;
	
	il = 0;
	ir = 0;
	
	i_xdiff = 0;
}

void update_powers()
{
	if (pow_right > 0)
	{
		ahead_R(pow_right);
	} 
	else if (pow_right < 0)
	{
		back_R(-pow_right);
	}
	else if (pow_right == 0)
	{
		stop_motor_R();
	} 
	
	if (pow_left >= 0)
	{
		ahead_L(pow_left);
	}
	else if (pow_left < 0)
	{
		back_L(-pow_left);
	}
	else if (pow_left == 0)
	{
		stop_motor_L();
	}
}

#ifdef __cplusplus
}
#endif