#ifndef ARRAYUTILS_HEADER
#define ARRAYUTILS_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <SDL.h>

int** imgToArray(SDL_Surface* img);

void freeUint8Array(int **arr, int rows);

void print_array2D(uint32_t **arr, size_t xmin, size_t xmax, size_t ymin, size_t ymax, int log);
#endif
