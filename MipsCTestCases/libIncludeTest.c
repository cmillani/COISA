#include "extras/lib/THING_ultrasonic.h"
#include "extras/lib/THING_encoder.h"
#include "extras/lib/THING_serial.h"
#include "extras/lib/THING_movement.h"

int main()
{
	int a = read_ultrasonic();
	configure_ultrasonic(CM);
	send_byte('a');
	char b = read_byte();
	int c = read_encoder_counter();
	int d = read_encoder_time();
	ahead();
	turn_right();
	turn_left();
	return 0;
}
