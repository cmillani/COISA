#line 1 "Blink.ino"
  
       
                                                                         

                                                                    
                                                                   
                                                                   
                                        

                                            

                     
                     
   


                                                                       
#include "Arduino.h"
#include <avr/sleep.h>
#include <vm.h>
#include <HAL.h>
#include <EH.h>
#include <inttypes.h>

#include <movement.h>
#include <encoder.h>
#include <timer.h>

#include <ultrasonic.h>

#include <avr/io.h>

#include <button.h>
void setup();
void loop();
#line 18

void test()
{
	
}

void setup() {
    eh_init();
	serial_configure(9600);
	init_timer();
    
	while(1)
	{
		uint8_t size1 = read_byte();
		uint8_t size2 = read_byte();
        
		uint16_t tot_size = (uint16_t)size1 | ((uint16_t)size2 << 8);
		int i;

		for (i = 0; i < tot_size; i++)
		{
			VM_memory[i] = read_byte();
		}

	#if MEASURING
		unsigned long tic = micros();
	#endif
	#if RUN_VM
		vm_cpu(0);
    #if EVENT_ON
        while(1)
        {
			if(timer_flag) 
			{
				timed_polling();
				timer_flag = 0;
			}
			consume_event();
		}
    #endif //EVENT ON
	#endif //RUN VM
	#if MEASURING
		unsigned long toc = micros();
		print("TIMESPENT.");
		printnum(toc - tic);
		print("\n");
	#endif
	}
}

                                                     
void loop() {

}