#line 1 "Blink.ino"
  
       
                                                                         

                                                                    
                                                                   
                                                                   
                                        

                                            

                     
                     
   


                                                                       
#include "Arduino.h"
#include "../src/vm.h"
#include "../src/HAL.h"
#include <inttypes.h>
void setup();
void loop();
#line 18
void setup() {
  Serial.begin(9600);
  Serial.println("Work in progress");
  vm_cpu();
}

                                                     
void loop() {
	Serial.println("End");
	delay(1000);
}

