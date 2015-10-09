#include "IntegralImage.h"

 
static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}
 

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    return *p;
  case 2:
    return *(Uint16 *)p;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
  case 4:
    return *(Uint32 *)p;
  }
  return 0;
}

 
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    *p = pixel;
    break;
  case 2:
    *(Uint16 *)p = pixel;
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
    *(Uint32 *)p = pixel;
    break;
  }
}


Uint32 sumRowII(SDL_Surface *img, int x, int y) {
	return (y == -1) ? 0 : sumRowII(img,x,y-1) + getpixel(img, x, y);
}

Uint32 sumII(SDL_Surface *img, int x, int y) {
	return (x == -1) ? 0 : sumII(img,x-1,y) + sumRowII(img,x,y);
}

void integralImg(SDL_Surface *img) {
	if(img == NULL) return;
	for(int i = 0; i < img->w; i++)
		for(int j = 0; j < img->h; j++)
			putpixel(img, i, j, sumII(img, i, j));
}

void imgToGreyScale(SDL_Surface *img) {
	Uint8 r, g, b;

	Uint32 pixel = 0;
	float luminance = 0.0;
	for(int i = 0; i < img->w; i++) {
		for(int j = 0; j < img->h; j++) {
			SDL_GetRGB(getpixel(img, i, j), img->format, &r, &g, &b);
			luminance = 0.299 * r + 0.587 * g + 0.114 * b;
			r = g = b = luminance / 3;
			pixel = SDL_MapRGB(img->format, r, g, b);
			putpixel(img, i, j, pixel);
		}
	}
}
