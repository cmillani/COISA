#include "src/vm.h"
#include "src/HAL.h"
#include <stdio.h>
#include <inttypes.h>

/*File for debug purpose only. To be used in order to load a binary into the vm*/

int manifest_state_machine(FILE * manifest);
int per_tag_checker(FILE * manifest);

const char * manifestables[] = {"USE_ENCODER", "USE_SERIAL", "USE_ULTRASONIC"};
char still_counting_man[] = {1,1,1};//Just a bool to signal that that manifestable should still be compared
const uint8_t number_of_manifestables = 3;
const char * start_tags[] = {"per"};
char still_counting_tag[] = {1};
const uint8_t number_of_tags = 1;

int main(int argc, char * argv[])
{
	FILE * manifest;
	FILE * binary;
	int i = 0;
	uint8_t byte;
	
	if (argc < 2) return 1;
	// printf("reading %s\n",argv[2]);
	// manifest = fopen(argv[2], "r");
	
	// if (!manifest_state_machine(manifest)) return 1; //TODO print error log
	
	// fclose(manifest);
	
	binary = fopen(argv[1], "rb");
	printf("Loading...\n");
	while(fread(&byte,sizeof(uint8_t),1,binary))
	{
		printf("%2x", byte);
		VM_memory[i] = byte;
		i++;
	}
	printf("\n");
	fclose(binary);
	printf("Starting VM:\n");
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
	char char_in;
	while ((char_in = fgetc(manifest)) != EOF) //Check for case where file ends before closing everything
	{
		int opened_tag = -1; //Flags what tag is opened
		int i, j = 0;
		int l;
		for (l = 0; l < number_of_tags; l ++)
		{
			still_counting_tag[l] = 1;
		}
		for (l = 0; l < number_of_manifestables; l ++)
		{
			still_counting_man[l] = 1;
		}
		printf("Char read: %c\n",char_in);
		if (char_in != '<') return 0; //Expected tag opening
		while ((char_in = fgetc(manifest)) != EOF)
		{
			if (char_in != '>')
			{
				for (i = 0; i < number_of_tags; i++)
				{
					printf("%c<>%c<>%d\n",char_in, start_tags[i][j], still_counting_tag[i]);
					if (still_counting_tag[i])
					{
						if (char_in != start_tags[i][j]) 
						{
							still_counting_tag[i] = 0;
						}
						else if (start_tags[i][j+1] == '\0')
						{
							printf("Tag >%d< ended\n",i);
							still_counting_tag[i] = 0;
							opened_tag = i; //This tag is selected until now, the next chat should be a closing char or the continuation of a bigger tag
						}
					}
				}
			}
			else 
			{
				printf("Breaking -> %c\n",char_in);
				break;//Close tag!
			}
			j++;
		}
		int selected_man = -1;
		if (opened_tag != -1)//Check what tag this is, or if it should return error;
		{
			//printf("Opened : %s\n",start_tags[opened_tag]);
			switch (opened_tag)
			{
				case 0:
				{
					selected_man = per_tag_checker(manifest);
					break;
				}
				default: return 0; //Error, should never reach here
			}
		}
		else return 0;
		
		if (selected_man != -1)
		{
			//printf("%d-%d-%d\n",HAS_ENCODER,HAS_SERIAL,HAS_ULTRASONIC);
			switch (selected_man)
			{
				case 0:
				{
					if (HAS_ENCODER) break;
					else return 0;
				}
				case 1:
				{
					if (HAS_SERIAL) break;
					else return 0;
				}
				case 2:
				{
					if (HAS_ULTRASONIC) break;
					else return 0;
				}
				default: return 0; //Error, should never reach here
			}
		}
		printf("Sensor passed.\n");
		//check /per> for end tag and then start aaaall over again for others sensors
		
		if ((char_in = fgetc(manifest)) != '/') return 0; //Expected tag closure
		int k = 0;
		while ((char_in = fgetc(manifest)) != EOF)
		{
			printf("Checking close tag %c-%c\n",start_tags[opened_tag][k], char_in);
			if (start_tags[opened_tag][k] != char_in) return 0;
			else if (start_tags[opened_tag][k+1] == '\0') break; 
			k++;
		}
		
		if ((char_in = fgetc(manifest)) != '>') return 0; //Expected this char in order to close tag
		//if (feof(manifest)) return 1;
	}
	return 1;
}

int per_tag_checker(FILE * manifest)
{
	printf("Checking Tag\n");
	char char_in;
	int selected_man = -1; //Flags what tag is opened
	int i, j = 0;
	while ((char_in = fgetc(manifest)) != EOF)
	{
		if (char_in != '<')
		{
			for (i = 0; i < number_of_manifestables; i++)
			{
				//printf("%c\n",char_in);
				if (still_counting_man[i])
				{
					if (char_in != manifestables[i][j]) 
					{
						printf("Man >%d< not valid anymore\n",i);
						still_counting_man[i] = 0;
					}
					else if (manifestables[i][j+1] == '\0')
					{
						printf("Man >%d< ended\n",i);
						still_counting_man[i] = 0;
						selected_man = i; //This tag is selected until now, the next chat should be a closing char or the continuation of a bigger tag
					}
				}
			}
		}
		else //Starting a tag (should be closure) 
		{
			return selected_man;
		}
		j++;
	}
	return selected_man;
}
