#ifndef _INTEGRAL_IMAGE_HEADER 
#define _INTEGRAL_IMAGE_HEADER
#include<stdint.h>
#include<SDL.h>

void integralImg(uint8_t **arr, int x, int y);

void imgToGreyScale(SDL_Surface* img, uint32_t** imgArr, uint8_t **arr);

#endif
