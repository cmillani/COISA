#include "src/vm.h"
#include "src/HAL.h"
#include <stdio.h>
#include <inttypes.h>

/*File for debug purpose only. To be used in order to load a binary into the vm*/

int manifest_state_machine(FILE * manifest);
const char distance_man[] = "USE_ULTRASONIC";
const char encoder_man[] = "USE_ENCODER";
const char serial_man[] = "USE_SERIAL";
const char start_tag[] = "<per>";
const char end_tag[] = "</per>";
const char * manifestables[] = {encoder_man, serial_man, distance_man};
const int number_of_manifestables = 3;

int main(int argc, char * argv[])
{
	FILE * manifest;
	FILE * binary;
	int i = 0;
	uint8_t byte;
	
	if (argc < 3) return 1;
	printf("reading %s\n",argv[2]);
	manifest = fopen(argv[2], "r");
	
	if (!manifest_state_machine(manifest)) return 1; //TODO print error log
	
	binary = fopen(argv[1], "rb");
	
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

int manifest_state_machine(FILE * manifest)
{
	/*The data will arrive one byte at a time and no buffer can be used in order to save memory. The manifest reader expects first a start tag, 
	then one of the available manifestables hardwares and finally the closing tag.
	Since there is no buffer, when checking for the hardware every available hardware of the list must be checked and, if a match does not occur 
	that hardware gets off the list. It ends when either the list is empty os the closing tag has started 
	
	State machine : opening tag -> respective handler for the tag -> closing tag
	Only 1 tag <per> up to date.*/
	return 1;
}
