#include "src/vm.h"
#include <stdio.h>
#include <inttypes.h>
/*
TODO -> tirar duvidas -> o que do header me é útil? preciso conferir endianess, machine...?
VM recebe um elf ou um hex?
Program header e section header
*/

uint32_t change_endianess(uint8_t * array, uint64_t size);

int main(int argc, char * argv[])
{
	uint8_t magic_number, bit_format, endianess, orig_version, so_abi, abi_info, ei_pad[7], e_type[2], e_machine[2], e_version[4], 
		e_entry[4], e_phoff[4], e_shoff[4], e_flags[4],	e_ehsize[2], e_phentsize[2], e_phnum[2], e_shentsize[2], e_shnum[2], e_shstrndx[2];
	char elf[3];
	if (argc < 2)
	{
		return(0);
	}
	FILE *elfBin;
	elfBin = fopen(argv[1], "rb");
	fread((void*)&magic_number, sizeof(uint8_t), 1,elfBin);
	fread((void*)elf, sizeof(char), 3,elfBin);
	fread((void*)&bit_format, sizeof(uint8_t), 1,elfBin);
	fread((void*)&endianess, sizeof(uint8_t), 1,elfBin);
	fread((void*)&orig_version, sizeof(uint8_t), 1,elfBin);
	fread((void*)&so_abi, sizeof(uint8_t), 1,elfBin);
	fread((void*)&abi_info, sizeof(uint8_t), 1,elfBin);
	fread((void*)ei_pad, sizeof(uint8_t), 7,elfBin);
	fread((void*)e_type, sizeof(uint8_t), 2,elfBin);
	fread((void*)e_machine, sizeof(uint8_t), 2,elfBin);
	fread((void*)e_version, sizeof(uint8_t), 4,elfBin);
	fread((void*)e_entry, sizeof(uint8_t), 4,elfBin);
	fread((void*)e_phoff, sizeof(uint8_t), 4,elfBin);
	fread((void*)e_shoff, sizeof(uint8_t), 4,elfBin);
	fread((void*)e_flags, sizeof(uint8_t), 4,elfBin);
	fread((void*)e_ehsize, sizeof(uint8_t), 2,elfBin);
	fread((void*)e_phentsize, sizeof(uint8_t), 2,elfBin);
	fread((void*)e_phnum, sizeof(uint8_t), 2,elfBin);
	fread((void*)e_shentsize, sizeof(uint8_t), 2,elfBin);
	fread((void*)e_shnum, sizeof(uint8_t), 2,elfBin);
	fread((void*)e_shstrndx, sizeof(uint8_t), 2,elfBin);
	printf("%x%c%c%c\n",magic_number, elf[0], elf[1], elf[2]);
	printf("%u,%u,%u,%u,%u\n",bit_format,endianess,orig_version,so_abi,abi_info);
	printf("??,%u,%u,%u,%u,%u,%u\n",change_endianess(e_type,2) ,e_type[0],e_type[1],so_abi,abi_info, 1);
	return 0;
}

uint32_t change_endianess(uint8_t * array, uint64_t size)
{
	uint32_t retval;
	uint64_t counter = 0;
	while (size > 0)
	{
		retval |= (array[counter] << (8*(size-1)));
		size--;
		counter++;
	}
	return retval;
}
