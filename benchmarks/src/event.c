#include "stdthing.h"

void test(void)
{
	print("ButtonPress\n");
}

int main()
{
	print("UHULL\n");
	eh_init();
	register_handler(1, test, "BTOG");
	init_button(0, 5);
}