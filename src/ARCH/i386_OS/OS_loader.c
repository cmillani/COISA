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
	struct timespec tic;
	clock_gettime(CLOCK_REALTIME, &tic);
	printf("%ld %ld %ld\n", tic.tv_sec, tic.tv_nsec, clock());
#endif
	vm_cpu();
#if MEASURING	
	struct timespec toc;
	clock_gettime(CLOCK_REALTIME ,&toc);
	printf("%ld %ld %ld\n", toc.tv_sec, toc.tv_nsec, clock());
#endif
	
#if MEASURING
//	printf("ç%fç\n", (toc - tic)/CLOCKS_PER_SEC);
#endif
	
	return 0;
}
