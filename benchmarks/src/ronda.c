#include "stdthing.h"

void turn(void)
{
	
}

int main()
{
	print("UHULL\n");
	eh_init();
	init_ultrasonic();
	register_us_handler(1, turn, "US_S", 20);
}