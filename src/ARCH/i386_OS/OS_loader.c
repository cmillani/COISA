#include "vm.h"
#include "HAL.h"
#include <stdio.h>
#include <inttypes.h>

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
	// printf("Loading...\n");
	while(fread(&byte,sizeof(uint8_t),1,binary))
	{
		VM_memory[i] = byte;
		i++;
	}
	// while (j < i)
	// {
	// 	printf("%2x: %2x%2x%2x%2x\n",j,VM_memory[j],VM_memory[j+1],VM_memory[j+2],VM_memory[j+3]);
	// 	j += 4;
	// }
	// printf("\n");
	fclose(binary);
	// printf("Starting VM:\n");
	vm_cpu();
	
	return 0;
}