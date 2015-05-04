#include "src/vm.h"
#include <stdio.h>
#include <inttypes.h>

int main(int argc, char * argv[])
{
	FILE * binary;
	int i = 0;
	uint8_t byte;
	
	binary = fopen("binary.bin", "rb");
	
	while(fread(&byte,sizeof(uint8_t),1,binary))
	{
		printf("%2x", byte);
		VM_memory[i] = byte;
		i++;
	}
	printf("\n");
	vm_cpu();
	
	return 0;
}