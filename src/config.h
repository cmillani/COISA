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
    

#ifndef CONFIG
#define CONFIG

#define DEBUGING 0
	
#define PRINTING 0
	
#define PRINTING_INST 0

#if ARCH
#include "ARCH/i386_OS/i386_OS.h"
#else
#include "ARCH/atmega328/atmega328.h"
#endif

#define HAS_MOTORS 1

#define HAS_ACCELEROMETER 0 //  TODO Define pins
	
#define HAS_GYROSCOPE 0
	
#define HAS_INFRARED 0
	
#define HAS_ENCODER 1
#if HAS_ENCODER
#define PIN_ENCODER1 
#define PIN_ENCODER2
#endif
	
#define HAS_ULTRASONIC 0
#if HAS_ULTRASONIC
#define PIN_ECHO
#define PIN_TRIG
#endif

#define HAS_SERIAL 1
#if HAS_SERIAL
#endif 

#endif /*CONFIG*/
    
#ifdef __cplusplus
}
#endif