#include "vm.h"
#include "HAL.h"
#include <stdio.h>
#include <inttypes.h>
#include <time.h>

/*File for debug purpose only. To be used in order to load a binary into the vm*/

int main(int argc, char * argv[])
{
	FILE * manifest;
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
	vm_cpu();
#endif
#if MEASURING	
	time_t toc = clock();
	printf("TIMESPENT.%ld\n", (toc - tic));
#endif
	i = 0;
	
	return 0;
}
