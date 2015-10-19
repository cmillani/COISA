#include "vm.h"
#include "HAL.h"
#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include <EH.h>

/*File for debug purpose only. To be used in order to load a binary into the vm*/

void blah(void)
{
	
}


int main(int argc, char * argv[])
{
	/*Debugging EH*/
	// print_EH();
// 	eh_init();
// 	print_EH();
// 	register_handler(1, blah);
// 	register_handler(2, blah + 1);
// 	register_handler(2, blah + 2);
// 	register_handler(3, blah + 3);
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
#endif
#if MEASURING	
	time_t toc = clock();
	printf("TIMESPENT.%ld\n", (toc - tic));
#endif
	i = 0;
	
	return 0;
}
