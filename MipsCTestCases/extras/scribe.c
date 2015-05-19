#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void select_output(const char * output_file_name);
void print_help(void);
void write_to_output(char * message);

bool has_a_name = false;
char * output_name;
FILE * output;

int main(int argc, char * argv[])
{
	/*The list of arguments on argv[0] consists of parameters to the manifest, declaring all the peripherals*/
	
	/*
		Official peripherals:
		Distance  - <per>USE_ULTRASONIC</per>
		Serial Comm - <per>USE_SERIAL</per>
		Optical Encoder - <per>USE_ENCODER</per>
	*/
	int i;
	char * buffer;
	
	
	if (argc < 2) 
	{
		printf("Not enough arguments for scribe\n");
		return 1; //Not enough arguments
	}
	
	buffer = (char *)malloc((75)*sizeof(char)); //75 = max string lenght
	strcpy(buffer, "\0");
	
	for (i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i],"-h"))
		{
			print_help();
		} 
		else if (!strcmp(argv[i], "-o")) 
		{
			if (i < argc -1 && argv[i + 1][0] != '-') 
			{
				select_output(argv[++i]);
			}
			else
			{
				printf("error: missing argument to '-o' (expected 1 value)\n");
				return 1;
			}
		}
		else if (!strcmp(argv[i], "-distance")) 
		{
			strcat(buffer, "<per>USE_ULTRASONIC</per>");
		}
		else if (!strcmp(argv[i], "-encoder")) 
		{
			strcat(buffer, "<per>USE_ENCODER</per>");
		}
		else if (!strcmp(argv[i], "-serial")) 
		{
			strcat(buffer, "<per>USE_SERIAL</per>");
		}
		else {
			printf("Unknown command \"%s\". Aborting.\n", argv[i]);
			return 1;
		}
	}
	printf("Opening file\n");
	if (has_a_name) output = fopen(output_name,"w");
	else output = fopen("a.manifest","w");
	write_to_output(buffer);
}

void write_to_output(char * message)
{
	printf("Will write to file\n");
	printf("%s\n", message);
	fprintf(output, "%s", message);
	//fopen()
}

void select_output(const char * output_file_name)
{
	printf("name_selected: %s\n",output_file_name);
	has_a_name = true;
	int lenght = strlen(output_file_name) + 1; //+ 1 due to '/0'
	output_name = (char *)malloc(lenght*sizeof(char));
	strcpy(output_name, output_file_name);
}

void print_help(void)
{
	/*List of possible parameters*/
	printf("OVERVIEW: manifest generator for a thing\n\n");
	printf("USAGE: scribe [options]\n\n");
	printf("OPTIONS:\n");
	printf("-h\t\tShows this message\n");
	printf("-o <file>\tWrite output to <file>\n");
	printf("-distance\tRequest to use distance sensor\n");
	printf("-encoder\tRequest to use encoder\n");
	printf("-serial\t\tRequest to use serial I/O\n");
}
