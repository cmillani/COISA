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

	// printnum(micros());
	// send_byte('\r');
	// send_byte('\n');
	// delay(1000);
	// printnum(micros());
	// send_byte('\r');
	// send_byte('\n');
	
	// unsigned int j;
	// j = TCNT1;
	// send_byte(j & 0xFF); //Echo the 1/4 of the binary that will be received
	// send_byte(' ');
	// send_byte((j>>8) & 0xFF);
	// send_byte('\r');
	// send_byte('\n');
	// // while (TCNT1 - j < 1000);
	// j = TCNT1;
	// printnum(j & 0xFF); //Echo the 1/4 of the binary that will be received
	// send_byte(' ');
	// printnum((j>>8) & 0xFF);
	// send_byte('\r');
	// send_byte('\n');
	
	for (i = 0; i < 4*tot_size; i++)
	{
		VM_memory[i] = read_byte();
	}
	// for (i = 0; i < 4*size; i++)
	// {
	// 	send_byte(VM_memory[i]);
	// }
#if MEASURING
	unsigned long tic = micros();
#endif
	vm_cpu();
#if MEASURING
	unsigned long toc = micros();
	printnum(toc - tic);
	print("\n");
#endif
	// send_byte(0x18);
}

                                                     
void loop() {
	// send_byte('O');send_byte('k');send_byte('\r');send_byte('\n');
	// delay(1000);
}

