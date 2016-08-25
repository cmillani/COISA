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
// #include <Wire.h>
#include <serial.h>

void mag_init(void) {
	i2c_start();
    if (i2c_get_status() != 0x08); {
		// printnum(i2c_get_status());
		// print("A\n");
	}
    //select device and send address bits
    i2c_write(0x3C);
    if (i2c_get_status() != 0x18); {
		// printnum(i2c_get_status());
		// print("B\n");
	}
    //Select Register
    i2c_write(0x02);
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
	
	// Wire.begin();
	// Wire.beginTransmission(addr); //start talking
	// Wire.write(0x02); // Set the Register
	// Wire.write(0x00); // Tell the HMC5883 to Continuously Measure
	// Wire.endTransmission();
}

int mag_x = 0;
int mag_y = 0; 
int mag_z = 0;

int last_x = 0;
int last_y = 0;
int last_z = 0;	

void mag_read(void) {
	int x,y,z;
	i2c_start();
    if (i2c_get_status() != 0x08); {
		// printnum(i2c_get_status());
		// print("E\n");
	}
    //select device and send address bits
    i2c_write(0x3C);
    if (i2c_get_status() != 0x18); {
		// printnum(i2c_get_status());
		// print("F\n");/
	}
	//start with register 3.
    i2c_write(0x03);
    if (i2c_get_status() != 0x28); {
		// printnum(i2c_get_status());
		// print("G\n");
	}
	
	//Starts to read
	i2c_start();
    if (i2c_get_status() != 0x10); {
		// printnum(i2c_get_status());
		// print("H\n");
	}
	
    i2c_write(0x3D);
    if (i2c_get_status() != 0x40); {
		// printnum(i2c_get_status());
		// print("I\n");
	}
	
	x = i2c_readACK() << 8;
    if (i2c_get_status() != 0x50); {
		// printnum(i2c_get_status());
		// print("J\n");
	}
	x |= i2c_readACK();
    if (i2c_get_status() != 0x50); {
		// printnum(i2c_get_status());
		// print("K\n");
	}
	z = i2c_readACK() << 8;
    if (i2c_get_status() != 0x50); {
		// printnum(i2c_get_status());
		// print("L\n");
	}
	z |= i2c_readACK();
    if (i2c_get_status() != 0x50); {
		// printnum(i2c_get_status());
		// print("M\n");
	}
	y = i2c_readACK() << 8;
    if (i2c_get_status() != 0x50); {
		// printnum(i2c_get_status());
		// print("N\n");
	}
	y |= i2c_readNACK();
    if (i2c_get_status() != 0x58); {
		// printnum(i2c_get_status());
		// print("O\n");
	}
	i2c_stop();
	
	last_x = mag_x;
	last_y = mag_y;
	last_z = mag_z;
	
	mag_x = mag_x*0.2 + x*0.6 + last_x*0.2;
	mag_y = mag_y*0.2 + y*0.6 + last_y*0.2;
	mag_z = mag_z*0.2 + z*0.6 + last_z*0.2;
	// Wire.beginTransmission(addr);
	// Wire.write(0x03);
	// Wire.endTransmission();
	// Wire.requestFrom(addr, 6);
	// if(6<=Wire.available()){
	// 	x = Wire.read()<<8; //MSB  x
	// 	x |= Wire.read(); //LSB  x
	// 	z = Wire.read()<<8; //MSB  z
	// 	z |= Wire.read(); //LSB z
	// 	y = Wire.read()<<8; //MSB y
	// 	y |= Wire.read(); //LSB y
	// }
}


void init_9ax(void) {
	i2c_start();
    if (i2c_get_status() != 0x08); {
		// printnum(i2c_get_status());
		// print("A\n");
	}
    //select device and send address bits
    i2c_write(0x68);
    if (i2c_get_status() != 0x18); {
		// printnum(i2c_get_status());
		// print("B\n");
	}
    //Wake up
    i2c_write(0x6b);
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

void read_9ax(void) {
	//0x68
}
	
#ifdef __cplusplus
}
#endif