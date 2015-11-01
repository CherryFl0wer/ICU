#ifndef _INTEGRAL_IMAGE_HEADER 
#define _INTEGRAL_IMAGE_HEADER
#include<stdint.h>
#include<SDL.h>

void integralImg(int **arr, int x, int y);

void imgToGreyScale(SDL_Surface* img);

#endif
