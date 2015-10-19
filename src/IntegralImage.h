#ifndef _INTEGRAL_IMAGE_HEADER 
#define _INTEGRAL_IMAGE_HEADER

#include<stdint.h>
#include<SDL.h>


uint32_t getpixel(SDL_Surface *surface, unsigned x, unsigned y);

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, uint32_t pixel);

void integralImg(uint8_t **arr, int x, int y);

void imgToGreyScale(SDL_Surface *img, uint8_t **arr);

#endif
