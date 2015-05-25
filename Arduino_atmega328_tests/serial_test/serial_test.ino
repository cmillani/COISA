#include "serial.h"
  char c;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  serial_init(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  c = serial_read();
  digitalWrite(6, (c & 1<<0));
  digitalWrite(7, (c & 1<<1));
  digitalWrite(8, (c & 1<<2));
  digitalWrite(9, (c & 1<<3));
  digitalWrite(10, (c & 1<<4));
  digitalWrite(11, (c & 1<<5));
  digitalWrite(12, (c & 1<<6));
  digitalWrite(13, (c & 1<<7));
  serial_send(c);
  //delay(1000);
}
