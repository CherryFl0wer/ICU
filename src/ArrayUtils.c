#include "ArrayUtils.h"

uint8_t** allocMemArr(int rows, int cols) {
	uint8_t		**arr;
	arr = malloc(rows * sizeof(uint8_t*));
	for(int i = 0; i < rows; i++)
		arr[i] = malloc(cols * sizeof(uint8_t));
	return arr;
}

void freeMemArr(uint8_t **arr, int rows) {
	for(int i = 0; i < rows; i++)
		free(arr[i]);

	free(arr);
}


void print_array2D(uint8_t **arr, size_t xmin, size_t xmax, size_t ymin, size_t ymax, int log) {	
	if(!log) {
		for(size_t x = xmin; x < xmax; ++x)
		{
			for(size_t y = ymin; y < ymax; ++y)
			{
				printf("\t (%zu,%zu)Val = %02u\n ",x,y,arr[x][y]);
			}
			printf("\n\n");
		}
	}
	else {
		FILE *log = NULL;
		log = fopen("./log.txt", "w+");
		fprintf(log, "----------------------------------\n");
		fprintf(log, "Array %zux%zu to %zux%zu\n\n", xmin, ymin, xmax,ymax);
		fprintf(log, "----------------------------------\n");
		for(size_t x = xmin; x < xmax; ++x)
		{
			for(size_t y = ymin; y < ymax; ++y)
			{
				fprintf(log, "(%zu,%zu)Val = %02u\n ",x,y,arr[x][y]);
			}
			fprintf(log, "\n\n");
		}
	
		fclose(log);
	}
}