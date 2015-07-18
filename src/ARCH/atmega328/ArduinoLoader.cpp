#line 1 "Blink.ino"
  
       
                                                                         

                                                                    
                                                                   
                                                                   
                                        

                                            

                     
                     
   


                                                                       
#include "Arduino.h"
#include "vm.h"
#include "HAL.h"
#include <inttypes.h>
void setup();
void loop();
#line 18
void setup() {
	serial_configure(9600);
	char size1 = read_byte();
	char size2 = read_byte();
	uint16_t tot_size = (uint16_t)size1 | ((uint16_t)size2 << 8);
	int i;
	send_byte(size1); //Echo the 1/4 of the binary that will be received
	send_byte('\r');
	send_byte('\n');
	send_byte(size2); //Echo the 1/4 of the binary that will be received
	send_byte('\r');
	send_byte('\n');
	
	for (i = 0; i < 4*tot_size; i++)
	{
		VM_memory[i] = read_byte();
	}
	// for (i = 0; i < 4*size; i++)
	// {
	// 	send_byte(VM_memory[i]);
	// }
	vm_cpu();
	// send_byte(0x18);
}

                                                     
void loop() {
	// send_byte('O');send_byte('k');send_byte('\r');send_byte('\n');
	// delay(1000);
}

