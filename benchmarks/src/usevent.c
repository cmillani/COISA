#include "stdthing.h"

void test(void)
{
	print("UEPAAAAAA\n");
}

int main()
{
	print("UHULL\n");
	eh_init();
	init_ultrasonic();
	// printnum(test);
	// print("UHULL\n");
	// printnum(&test);
	register_us_handler(1, test, "US_S", 15);
	// printnum(test);
	// print("UHULL\n");
	// printnum(&test);
	// print("UHULL\n");
}