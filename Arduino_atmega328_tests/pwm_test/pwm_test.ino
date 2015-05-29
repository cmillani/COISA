#include "pwm.h"
void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  //set_PWM(1, 255);
  set_PWM(3, 255);
  set_PWM(2, 255);
  delay(1000);
  //set_PWM(1, 10);
  set_PWM(3, 10);
  set_PWM(2, 10);
}

void loop() {
  // put your main code here, to run repeatedly:

}
