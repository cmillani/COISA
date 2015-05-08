#include "vm.h"
#include "syscall.h"
#include <setjmp.h>

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
/*
Code for testing the basics of the VM
*/
jmp_buf event_check, back_to_vm;

static volatile int toggle = 0;

ISR(USART_RX_vect)
{
  toggle = 1;
}

int state;

void setup() {
  
  DDRB |= (0x1 << 5);
  PORTB ^= (0x1 << 5);

  delay(500);  
  
  PORTB ^= (0x1 << 5); //Blink led 13, just for fun
  
  UBRR0L = (uint8_t)(BAUD_PRESCALE & 0xff);
  UBRR0H = (uint8_t)(BAUD_PRESCALE >> 8);
  UCSR0B =
      /* interrupt on receive */
      (1 << RXCIE0) |
      (1 << RXEN0);
  UCSR0C =
      /* no parity bit */
      (0 << UPM01) |
      (0 << UPM00) |
      /* asyncrounous USART */
      (0 << UMSEL01) |
      (0 << UMSEL00) |
      /* one stop bit */
      (0 << USBS0) |
      /* 8-bits of data */
      (1 << UCSZ01) |
      (1 << UCSZ00);
  
  sei();

  if (setjmp(event_check))
  {
    
  }
  else
  {
    //vm_cpu();
  }
  
  while (!toggle);
  {
    state = state? 0:1;
    toggle = 0;
  }
  PORTB = state ? 0x20 : 0; 
  
}

void loop() {
  pinMode(13,LOW);
}

void serialEvent(){
//statements
}
