#ifndef ARRAYUTILS_HEADER
#define ARRAYUTILS_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <SDL.h>

uint8_t** imgToArray(SDL_Surface* img);

void freeUint8Array(uint8_t **arr, int rows);

void print_array2D(uint8_t **arr, size_t xmin, size_t xmax, size_t ymin, size_t ymax, int log);
#endif
