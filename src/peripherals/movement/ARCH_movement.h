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
	
#ifndef ARCH_MOVEMENT
#define ARCH_MOVEMENT
	
void ahead(void);
void turn_left(void);
void turn_right(void);
void setup_movement(void);


void ahead_L(void);
void ahead_R(void);
void back_R(void);
void back_L(void);
void stop_motor_L(void);//Turn off left motor
void stop_motor_R(void);//Turn off right motor 
void control(void);
void PID(void);
void PID_ON(void);
void set_targetRPM_R(int rpm);
void set_targetRPM_L(int rpm);

#endif

#ifdef __cplusplus
}
#endif