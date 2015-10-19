#ifndef _ARRAY_UTILS_HEADER
#define _ARRAY_UTILS_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

uint8_t** allocMemArr(int rows, int cols);

void freeMemArr(uint8_t **arr, int rows);

void print_array2D(uint8_t **arr, size_t xmin, size_t xmax, size_t ymin, size_t ymax, int log);
#endif
