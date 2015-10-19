#include "IntegralImage.h"

 
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

void integralImg(uint8_t **arr, int x, int y) { 

	for(int i = 1; i < x; i++)
		arr[i][0] += arr[i-1][0]; 
	
	for(int j = 1; j < y; j++)
		arr[0][j] += arr[0][j-1];

	for(int j = 1; j < y; j++)
		for(int i = 1; i < x; i++)
			arr[i][j] +=  arr[i-1][j] + arr[i][j-1] - arr[i-1][j-1]; 	

}


void imgToGreyScale(SDL_Surface *img, uint8_t **bwImgTab) {
	uint8_t r, g, b;

 //	uint32_t pixel = 0;
	float luminance = 0.0;
	for(int i = 0; i < img->w; i++) {
		for(int j = 0; j < img->h; j++) {
			SDL_GetRGB(getpixel(img, i, j), img->format, &r, &g, &b);
			luminance = 0.299 * r + 0.587 * g + 0.114 * b;
			r = g = b = luminance / 3;
			bwImgTab[i][j] = r; // or g or b whatever
		//	pixel = SDL_MapRGB(img->format, r, g, b);
		//	putpixel(img, i, j, pixel);
		}
	}
}
