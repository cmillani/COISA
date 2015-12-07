#include "stdthing.h"

void test(void)
{
	print("ButtonPress\n");
}

int main()
{
	print("UHULL\n");
	eh_init();
	// printnum(test);
	// print("UHULL\n");
	// printnum(&test);
	register_handler(1, test, "BTOG");
	// printnum(test);
	// print("UHULL\n");
	// printnum(&test);
	// print("UHULL\n");
	init_button(0, 5);
}