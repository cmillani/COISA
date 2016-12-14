#include <avr/io.h>
#include <util/delay.h>
int main() {
	DDRC = 0xFF; //Nakes PORTC as Output
	while(1) //infinite loop
	{
		PORTC = 0xFF; //Turns ON All LEDs
		_delay_ms(1000); //1 second delay
		PORTC= 0x00; //Turns OFF All LEDs
		_delay_ms(1000); //1 second delay
	}
	return 0;
}
