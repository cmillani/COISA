#include "vm.h"
#include "HAL.h"
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <EH.h>

/*File for debug purpose only. To be used in order to load a binary into the vm*/

void blah(void)
{
	
}


int main(int argc, char * argv[])
{
	/*Debugging EH*/
	// char a[] = "A";
	// char b[] = "B";
	// char c[] = "C";
	// char d[] = "D";
	// print_EH();
	// eh_init();
	// print_EH();
	// register_handler(1, blah, a);
	// register_handler(2, blah + 1, b);
	// register_handler(2, blah + 2, c);
	// register_handler(2, blah + 3, d);
	// register_handler(2, blah + 4, "E");
	// print_EH();
	// register_handler(1, blah+5, a);
	// insert_event(1, a);
	// insert_event(2, b);
// 	insert_event(3);
// 	insert_event(1);
	// print_EH();
	// consume_event();
// 	consume_event();
// 	consume_event();
// 	consume_event();
	// print_EH();
	// print("Will Work");
// 	insert_event(1);
// 	insert_event(2);
// 	insert_event(3);
// 	insert_event(1);
// 	print_EH();
// 	consume_event();
// 	consume_event();
// 	consume_event();
// 	consume_event();
// 	print_EH();
// 	insert_event(1);
// 	insert_event(2);
// 	insert_event(3);
// 	insert_event(1);
// 	print_EH();
// 	consume_event();
// 	consume_event();
// 	consume_event();
// 	consume_event();
// 	print_EH();
	/*End Debugging EH*/
	FILE * binary;
	int i = 0, j = 0;
	uint8_t byte;
	
	if (argc < 2) 
	{
		printf("Expected file name, aborting\n");
		return 1;
	}

	binary = fopen(argv[1], "rb");

	while(fread(&byte,sizeof(uint8_t),1,binary))
	{
		VM_memory[i] = byte;
		i++;
	}

	fclose(binary);
#if MEASURING
	time_t tic = clock();
#endif
#if RUN_VM
	vm_cpu(0);
	// print_EH();
	// print_EH();
	// vm_cpu(ehvec[0]);
#endif
#if MEASURING	
	time_t toc = clock();
	printf("TIMESPENT.%ld\n", (toc - tic));
#endif
	// i = 0;
	
	return 0;
}
