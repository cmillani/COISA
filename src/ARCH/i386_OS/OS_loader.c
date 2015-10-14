#include "vm.h"
#include "HAL.h"
#include <stdio.h>
#include <inttypes.h>
#include <time.h>

/*File for debug purpose only. To be used in order to load a binary into the vm*/

#include <EH.h>
void print_EH(void)
{
	printf("*---------------------------------------------------------*\n");
	printf("EH:\n");
	printf("Events:\t");
	for (int i = 0; i < EVENTQTTY; i++)
	{
		printf("%d,%d,%d\t", ehvecpointers[i].id, ehvecpointers[i].pos, ehvecpointers[i].sz);
	}
	printf("\n");
	printf("Handlers:\t");
	for (int i = 0; i < EHVECSZ; i++)
	{
		printf("%p\t", ehvec[i]);
	}
	printf("\n");
	printf("Queue:\t");
	for (int i = 0; i < EHQUEUESZ; i++)
	{
		printf("%d\t", ehqueue[i]);
	}
	printf("Init:%d,Sz:%d\n", queue_init, queue_size);
	printf("*---------------------------------------------------------*\n");
}
void blah(void)
{
	
}


int main(int argc, char * argv[])
{
	/*Debugging EH*/
	print_EH();
	eh_init();
	print_EH();	
	register_handler(1, blah);
	register_handler(2, blah + 1);
	register_handler(3, blah + 2);
	print_EH();
	// remove_handler(1, blah);
	print_EH();
	register_handler(2, blah + 3);
	print_EH();
	insert_event(1);
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
	vm_cpu();
#endif
#if MEASURING	
	time_t toc = clock();
	printf("TIMESPENT.%ld\n", (toc - tic));
#endif
	i = 0;
	
	return 0;
}
