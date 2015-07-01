#include "extras/lib/THING_ultrasonic.h"
#include "extras/lib/THING_encoder.h"
#include "extras/lib/THING_serial.h"
#include "extras/lib/THING_movement.h"

int main()
{
	int a = read_ultrasonic();
	configure_ultrasonic(CM);
	serial_configure(9600);
	send_byte('a');
	char b = read_byte();
	int c = read_encoder_counter(RIGHT);
	int d = read_encoder_time(RIGHT);
	ahead();
	turn_right();
	turn_left();
	return 0;
}
