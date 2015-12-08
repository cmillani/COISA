#line 1 "Blink.ino"
  
       
                                                                         

                                                                    
                                                                   
                                                                   
                                        

                                            

                     
                     
   


                                                                       
#include "Arduino.h"
#include <vm.h>
#include <HAL.h>
#include <EH.h>
#include <inttypes.h>

#include <movement.h>
#include <encoder.h>
#include <timer.h>

#include <avr/io.h>

#include <button.h>
void setup();
void loop();
#line 18

void test()
{
	
}

void setup() {
	// eh_init();
	serial_configure(9600);
	// init_button(BPORT, 5);
	// register_handler(1, test, "BTOG");
	
	// while(1)
	// {
	// 	for (int i = 0; i < EHQUEUESZ; i++)
	// 	 		{
	// 	 			printnum(ehqueue[i].id);
	// 	 			print(" ");
	// 	 			print(ehqueue[i].name);
	// 	 			print("\t");
	// 	 		}
	// 	 		// printnum(timerOvfcnt);
	//  		print("\n");
	// 	// consume_event();
	//
	// }
	// setup_movement();
	// ahead_L();
	// ahead_R();
	// while(1)
	// {
		// printnum(read_encoder_counter(LEFT));
		// print("-");
		// printnum(read_encoder_time(LEFT));
		// print("\n");
	// }
	// stop_motor_L();
	// stop_motor_R();
	while(1)
	{
		init_timer();
		while(1)
		{
			if(timer_flag) 
			{
				print("FOE\n");
				timer_flag = 0;
			}
			// printnum(timerOvfcnt);
			// print("\n");
		}
		// setup_movement();
		// ahead();
		// while(1);
		// DDRB |= (1 << PB5);
		// PORTB |= (1 << PB5);
		// init_timer();
		// start_encoder();
	    // TCCR0B |= (1 << CS01);
		// setup_movement();
		// while(1)
		// {
			// printnum(TCNT2);
			// print("\n");
		// }
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

		for (i = 0; i < tot_size; i++)
		{
			VM_memory[i] = read_byte();
			//send_byte(VM_memory[i]);
		}
		
		// for (i = 0; i < 1700; i++)
		// {
		// 	printnum(VM_memory[i]);
		// 	print("-");
		// }
		// print("\n");

	#if MEASURING
		unsigned long tic = micros();
	#endif
	#if RUN_VM
		// print("Um\n");
		vm_cpu(0);
		// print("Dois\n");hand_addr
		// RF[4] = ehvec[0];
		// printnum(ehvec[0]);
		// print("\n");
		// RF[4] = ehvec[0];
		// vm_cpu(hand_addr);
		// vm_cpu(60);
		// vm_cpu(ehvec[0]);
		while(1)
		{
// 			// for (int i = 0; i < EHQUEUESZ; i++)
// 			// 	 		{
// 			// 	 			printnum(ehqueue[i].id);
// 			// 	 			print(" ");
// 			// 	 			print(ehqueue[i].name);
// 			// 	 			print("\t");
// 			// 	 		}
// 			// print("\n");
//			
			if(timer_flag) 
			{
				timed_polling();
				timer_flag = 0;
			}
			consume_event();
		}
	#endif
	#if MEASURING
		unsigned long toc = micros();
		print("TIMESPENT.");
		printnum(toc - tic);
		print("\n");
	#endif
		// print("End\n");
		// send_byte('\0');
	}
}

                                                     
void loop() {

}