#ifndef SDLPIXEL_HEADER
#define SDLPIXEL_HEADER
#include<stdint.h>
#include<SDL.h>
#include<SDL_image.h>

uint32_t getpixel(SDL_Surface *surface, unsigned x, unsigned y);

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, uint32_t pixel);

int SDLInit(void);

SDL_Surface* loadimg(const char* path);

void displayImg(SDL_Surface* img);
#endif
