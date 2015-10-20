#include <stdio.h>
void write_on_file(char *file_name, char *string_to_write)
{
	FILE* file = NULL;

	file = fopen(file_name, "r+");

	if(file != NULL)
	{
		fputs(string_to_write, file);

		fclose(file);
	}
	else
	{
		printf("The file %s is inaccessible", file_name);
	}
}

int main(int argc, char *argv[])
{
	write_on_file("test.txt", "|kyle|2|kyle_p1.jpg|kyle_p2.jpg|\n");

	argc = 0;
	argv = NULL;

	return 0;
}
