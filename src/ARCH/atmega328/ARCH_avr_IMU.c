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
	
#include <stdint.h>
#include <timer.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <ARCH_magnetometer.h>
#include <i2c.h>
#include <IMU.h>
#include <math.h>
#include <stdlib.h>
// #include <Wire.h>
#include <serial.h>
	
void complementary_filter();
	
void init_IMU(void) {
	i2c_start();
    if (i2c_get_status() != 0x08); {
		// printnum(i2c_get_status());
		// print("A\n");
	}
    //select device and send address bits
    i2c_write(0xD0);
    if (i2c_get_status() != 0x18); {
		// printnum(i2c_get_status());
		// print("B\n");
	}
    //Select Register
    i2c_write(0x6B);
    if (i2c_get_status() != 0x28); {
		// printnum(i2c_get_status());
		// print("C\n");
	}
	//Configures as continuous measuring
    i2c_write(0x00);
    if (i2c_get_status() != 0x28); {
		// printnum(i2c_get_status());
		// print("D\n");
	}
	
    i2c_stop();
    return;
}
	
int AcX, AcY, AcZ;
int GyX, GyY, GyZ;
int temperature;
	
void read_IMU(void) {
	i2c_start();
    if (i2c_get_status() != 0x08); {
		// printnum(i2c_get_status());
		// print("A\n");
	}
    //select device and send address bits
    i2c_write(0xD0);
    if (i2c_get_status() != 0x18); {
		// printnum(i2c_get_status());
		// print("B\n");
	}
    //Select Register
    i2c_write(0x3B);
    if (i2c_get_status() != 0x28); {
		// printnum(i2c_get_status());
		// print("C\n");
	}
	//Restarts to read
	i2c_start();
    if (i2c_get_status() != 0x10); {
		// printnum(i2c_get_status());
		// print("H\n");
	}
	
    i2c_write(0xD1);
    if (i2c_get_status() != 0x40); {
		// printnum(i2c_get_status());
		// print("I\n");
	}
	/**************************************************/	
	AcX = i2c_readACK() << 8;
    if (i2c_get_status() != 0x50); {
		// printnum(i2c_get_status());
		// print("J\n");
	}
	AcX |= i2c_readACK();
    if (i2c_get_status() != 0x50); {
		// printnum(i2c_get_status());
		// print("K\n");
	}
	/**************************************************/
	AcY = i2c_readACK() << 8;
    if (i2c_get_status() != 0x50); {
		// printnum(i2c_get_status());
		// print("L\n");
	}
	AcY |= i2c_readACK();
    if (i2c_get_status() != 0x50); {
		// printnum(i2c_get_status());
		// print("M\n");
	}
	/**************************************************/
	AcZ = i2c_readACK() << 8;
    if (i2c_get_status() != 0x50); {
		// printnum(i2c_get_status());
		// print("N\n");
	}
	AcZ |= i2c_readACK();
    if (i2c_get_status() != 0x50); {
		// printnum(i2c_get_status());
		// print("O\n");
	}
	/**************************************************/
	temperature = i2c_readACK() << 8;
    if (i2c_get_status() != 0x50); {
		// printnum(i2c_get_status());
		// print("N\n");
	}
	temperature |= i2c_readACK();
    if (i2c_get_status() != 0x50); {
		// printnum(i2c_get_status());
		// print("O\n");
	}
	/**************************************************/
	GyX = i2c_readACK() << 8;
    if (i2c_get_status() != 0x50); {
		// printnum(i2c_get_status());
		// print("N\n");
	}
	GyX |= i2c_readACK();
    if (i2c_get_status() != 0x50); {
		// printnum(i2c_get_status());
		// print("O\n");
	}
	/**************************************************/
	GyY = i2c_readACK() << 8;
    if (i2c_get_status() != 0x50); {
		// printnum(i2c_get_status());
		// print("N\n");
	}
	GyY |= i2c_readACK();
    if (i2c_get_status() != 0x50); {
		// printnum(i2c_get_status());
		// print("O\n");
	}
	/**************************************************/
	GyZ = i2c_readACK() << 8;
    if (i2c_get_status() != 0x50); {
		// printnum(i2c_get_status());
		// print("N\n");
	}
	GyZ |= i2c_readNACK();
    if (i2c_get_status() != 0x58); {
		// printnum(i2c_get_status());
		// print("O\n");
	}
	/**************************************************/
	
    i2c_stop();
	
	// printnum(GyX);
// 	print("\t");
// 	printnum(GyY);
// 	print("\t");
// 	printnum(GyZ);
// 	print("\t");
// 	printnum(AcX);
// 	print("\t");
// 	printnum(AcY);
// 	print("\t");
// 	printnum(AcZ);
// 	print("\n");
	complementary_filter();
}

#define ACCELEROMETER_SENSITIVITY 8192.0
#define GYROSCOPE_SENSITIVITY 65.536
 
#define M_PI 3.14159265359	    
 
#define dt 0.01

float pitch = 0;
float roll = 0;
float yaw = 0;
 
void complementary_filter() {
	float pitchAcc, rollAcc, yawAcc;               
 
    // Integrate the gyroscope data -> int(angularSpeed) = angle
    pitch += ((float)GyX / GYROSCOPE_SENSITIVITY) * dt; // Angle around the X-axis
    roll -= ((float)GyY / GYROSCOPE_SENSITIVITY) * dt;    // Angle around the Y-axis
	yaw += ((float)GyZ / GYROSCOPE_SENSITIVITY) * dt;

    // Compensate for drift with accelerometer data if !bullshit
    // Sensitivity = -2 to 2 G at 16Bit -> 2G = 32768 && 0.5G = 8192
    int forceMagnitudeApprox = abs(AcX) + abs(AcY) + abs(AcZ);
    if (forceMagnitudeApprox > 8192 && forceMagnitudeApprox < 32768)
    {
	// Turning around the X axis results in a vector on the Y-axis
        pitchAcc = atan2f((float)AcY, (float)AcZ) * 180 / M_PI;
        pitch = pitch * 0.98 + pitchAcc * 0.02;

	// Turning around the Y axis results in a vector on the X-axis
        rollAcc = atan2f((float)AcX, (float)AcZ) * 180 / M_PI;
        roll = roll * 0.98 + rollAcc * 0.02;
		
	// Turning around the Z axis results in a vector on the ?-axis
		yawAcc = atan2f((float)AcX, (float)AcY) * 180 / M_PI;
		yaw = yaw * 0.98 + yawAcc * 0.02;
    }
	printnum((int)roll);
	print("\t");
	printnum((int)pitch);
	print("\t");
	printnum((int)yaw);
	print("\n");
}
	
#ifdef __cplusplus
}
#endif