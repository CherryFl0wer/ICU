#include "SDLPixel.h"

static inline
uint8_t* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}
 

uint32_t getpixel(SDL_Surface *surface, unsigned x, unsigned y) {
  uint8_t *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    return *p;
  case 2:
    return *(uint16_t *)p;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
  case 4:
    return *(uint32_t *)p;
  }
  return 0;
}

 
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, uint32_t pixel) {
  uint8_t *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    *p = pixel;
    break;
  case 2:
    *(uint16_t *)p = pixel;
    break;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
      p[0] = (pixel >> 16) & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = pixel & 0xff;
    } else {
      p[0] = pixel & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = (pixel >> 16) & 0xff;
    }
    break;
  case 4:
    *(uint32_t *)p = pixel;
    break;
  }

}


int SDLInit(void) {
	if(SDL_Init(SDL_INIT_VIDEO) == -1) 	{
		printf("SDL_Init : %s\n", SDL_GetError());
		return 0;
	}
	
	return 1;
}


SDL_Surface* loadimg(const char* path) {
	SDL_Surface* img = IMG_Load(path);
	if(!img) {
		printf("Image failed to load %s \n", IMG_GetError());
		SDL_Quit();
		img = NULL;
	}

	return img;
}


void displayImg(SDL_Surface* img) {
	SDL_Surface* screen;
	SDL_Event event;
	screen = SDL_SetVideoMode(img->w, img->h, img->format->BitsPerPixel, SDL_ANYFORMAT);
	int done = 0;

	if(!screen) {
		printf("SDL_SetVideoMode %s \n", SDL_GetError());
		SDL_FreeSurface(img);
		SDL_Quit();
	}
	
	SDL_BlitSurface(img, 0, screen, 0);
	SDL_Flip(screen);

	while(!done && SDL_WaitEvent(&event) != -1) {
 		switch(event.type) {
			case SDL_KEYDOWN:
			case SDL_QUIT:
				done = 1;
				break;
			case SDL_VIDEOEXPOSE:
				SDL_BlitSurface(img, 0, screen, 0);
				SDL_Flip(screen);
				break;
			default:
				break;
		} 
	}

	SDL_FreeSurface(img);
	SDL_Quit();
}
