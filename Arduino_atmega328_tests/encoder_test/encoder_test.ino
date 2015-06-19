#include "encoder.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  start_encoder();
}

int a,b;

void loop() {
  // put your main code here, to run repeatedly:
//  PORTB |= (1 << 5);
  //PORTB &= ~(1 << 5);
  Serial.print(read_encoder_counter(RIGHT));
  Serial.println(read_encoder_counter(LEFT));
}
