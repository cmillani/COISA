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
/*Description: HAL being developed in order to abstract the sensor hardware connected to a microprocessor.
 *It's intended to be used with a VM to make possible an easier programming of a robot or device.
 * 
 * Possible sensors:
 * 
 * Encoder to count the rotations of the motor
 * Ultrasonic distance sensor
 * Infrared reflectance sensor
 * Gyroscope
 * Accelerometer
 * */
#ifdef __cplusplus
extern "C" {
#endif
    

#ifndef HAL
#define HAL

#include "config.h" 

#include <stdint.h>

/**************************************************************************/
/*******************************HAL functions******************************/
/**************************************************************************/

// uint32_t hal_;

uint8_t hal_call(uint32_t sensid, char identifier[]);//Call to hardware I/O

#if HAS_ULTRASONIC
#include "ultrasonic.h"
#endif

#if HAS_ENCODER
#include "encoder.h"
#endif

#if HAS_INFRARED

#endif

#if HAS_GYROSCOPE

#endif

#if HAS_ACCELEROMETER

#endif

#if HAS_SERIAL
#include "serial.h"
#endif

#if HAS_MOTORS
#include "movement.h"
#endif

#if HAS_BUTTON
#include <button.h>
#endif

#endif /*HAL*/

#ifdef __cplusplus
}
#endif
