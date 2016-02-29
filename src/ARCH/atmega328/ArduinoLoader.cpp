#line 1 "Blink.ino"
  
       
                                                                         

                                                                    
                                                                   
                                                                   
                                        

                                            

                     
                     
   


                                                                       
#include "Arduino.h"

#ifdef SIMAVR
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#endif

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

#if SIMAVR
const int progSize PROGMEM = 408;
const uint8_t progBin[] PROGMEM = {36, 2, 0, 11, 0, 0, 0, 12, 12, 0, 0, 6, 0, 0, 0, 0, 36, 2, 0, 10, 0, 0, 0, 12, 39, 189, 255, 232, 175, 191, 0, 20, 60, 1, 0, 0, 140, 36, 1, 148, 36, 2, 255, 156, 60, 1, 29, 247, 52, 35, 86, 129, 0, 4, 8, 128, 0, 36, 8, 33, 0, 4, 41, 64, 0, 161, 8, 33, 0, 4, 42, 0, 0, 161, 8, 35, 0, 4, 35, 0, 0, 129, 8, 35, 36, 33, 115, 133, 0, 35, 0, 25, 0, 0, 32, 16, 36, 66, 0, 1, 0, 4, 35, 130, 0, 4, 41, 128, 0, 4, 49, 192, 0, 197, 40, 33, 0, 4, 50, 64, 0, 197, 40, 33, 0, 4, 51, 64, 0, 197, 40, 33, 0, 4, 36, 64, 0, 133, 32, 33, 20, 64, 255, 233, 0, 36, 32, 35, 60, 1, 0, 0, 12, 0, 0, 90, 172, 36, 1, 148, 60, 1, 0, 0, 12, 0, 0, 95, 36, 36, 1, 144, 36, 2, 0, 0, 143, 191, 0, 20, 3, 224, 0, 8, 39, 189, 0, 24, 60, 1, 0, 0, 140, 34, 1, 148, 0, 2, 24, 128, 0, 98, 24, 33, 0, 2, 33, 64, 0, 131, 24, 33, 0, 2, 34, 0, 60, 5, 29, 247, 0, 131, 24, 35, 52, 164, 86, 129, 0, 2, 19, 0, 0, 67, 16, 35, 36, 66, 115, 133, 0, 68, 0, 25, 0, 0, 24, 16, 0, 3, 27, 130, 0, 3, 33, 128, 0, 3, 41, 192, 0, 164, 32, 33, 0, 3, 42, 64, 0, 164, 32, 33, 0, 3, 43, 64, 0, 164, 32, 33, 0, 3, 28, 64, 0, 100, 24, 33, 0, 67, 16, 35, 3, 224, 0, 8, 172, 34, 1, 148, 36, 2, 0, 12, 36, 3, 0, 10, 0, 0, 0, 12, 3, 224, 0, 8, 0, 0, 0, 0, 36, 2, 0, 12, 36, 3, 0, 11, 0, 0, 0, 12, 3, 224, 0, 8, 0, 0, 0, 0, 36, 2, 0, 12, 36, 3, 0, 12, 0, 0, 0, 12, 3, 224, 0, 8, 0, 0, 0, 0, 36, 2, 0, 12, 36, 3, 0, 13, 0, 0, 0, 12, 3, 224, 0, 8, 0, 0, 0, 0, 36, 2, 0, 12, 36, 3, 0, 14, 0, 0, 0, 12, 3, 224, 0, 8, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 42};
#endif
void setup() {
    eh_init();
	serial_configure(9600);
	init_timer();
	
	while(1)
	{
#if SIMAVR
        for (int i = 0; i<progSize; i++)
        {
            VM_memory[i] = pgm_read_word_near(progBin+i);
        }
#else
		uint8_t size1 = read_byte();
		uint8_t size2 = read_byte();
        
		uint16_t tot_size = (uint16_t)size1 | ((uint16_t)size2 << 8);
		int i;
        // printnum(size1);
        // print("\n");
        // printnum(size2);
        // print("\n");
		for (i = 0; i < tot_size; i++)
		{
			VM_memory[i] = read_byte();
            // printnum(i);
            // print("\n");
		}
    
#endif

	#if MEASURING
		unsigned long tic = micros();
	#endif
	#if RUN_VM
        vm_cpu(0);
    #if MEASURING
    	unsigned long toc = micros();
    	print("TIMESPENT.");
    	printnum(toc - tic);
    	print("\n");
    #endif
    #if SIMAVR
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        cli();
        sleep_enable();
        sleep_bod_disable();
        sei();
        sleep_cpu();
        sleep_disable();
    #endif //SIMAVR
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
	}
}

                                                     
void loop() {

}