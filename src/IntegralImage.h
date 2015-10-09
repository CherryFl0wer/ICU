#ifndef _II_HEADER 
#define _II_HEADER

#include<stdint.h>
#include<SDL.h>

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

Uint32 sumRowII(SDL_Surface *img, int x, int y);

Uint32 sumII(SDL_Surface *img, int x, int y);

void integralImg(SDL_Surface *img);

void imgToGreyScale(SDL_Surface *img);
#endif
