#line 1 "Blink.ino"
  
       
                                                                         

                                                                    
                                                                   
                                                                   
                                        

                                            

                     
                     
   


                                                                       
#include "Arduino.h"
#include <vm.h>
#include <HAL.h>
#include <inttypes.h>

#include <movement.h>
#include <encoder.h>
#include <timer.h>
void setup();
void loop();
#line 18

void setup() {
	serial_configure(9600);
	DDRB |= (1 << PB5);
	// PORTB |= (1 << PB5);
	init_timer();
	// start_encoder();
    // TCCR0B |= (1 << CS01);
	// setup_movement();
	while(1)
	{
		// printnum(TCNT2);
		// print("\n");
	}
	// setup_movement();
	// ahead();
	// printnum(read_encoder_counter(LEFT));
	// print("-");
	// printnum(read_encoder_counter(RIGHT));
	// print("\n");
	// stop_motor_R();
	// stop_motor_L();
	uint8_t size1 = read_byte();
	uint8_t size2 = read_byte();
	// send_byte(size1);
	// send_byte(size2);
	uint16_t tot_size = (uint16_t)size1 | ((uint16_t)size2 << 8);
	int i;

	for (i = 0; i < 4*tot_size; i++)
	{
		VM_memory[i] = read_byte();
		//send_byte(VM_memory[i]);
	}

#if MEASURING
	unsigned long tic = micros();
#endif
#if RUN_VM
	vm_cpu(0);
#endif
#if MEASURING
	unsigned long toc = micros();
	print("TIMESPENT.");
	printnum(toc - tic);
	print("\n");
#endif
	send_byte('\0');
}

                                                     
void loop() {

}