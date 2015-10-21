#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <SDL_image.h>

// Personal Headers

#include "./src/IntegralImage.h"
#include "./src/ArrayUtils.h"
#include "./src/SDLPixel.h"
#include "./src/Treatment.h"

int main(int argc, const char* argv[])
{
  SDL_Surface  *image;	

  if(argc != 2) return 1;
	
	SDLInit();

  image = loadimg(argv[1]);

	// _____________________ //
	
	SDL_LockSurface(image);

 	imgToGreyScale(image);
	normalize(image);
	equalize(image);
	uint8_t **tabImg = imgToArray(image);
	integralImg(tabImg, image->w, image->h);

	SDL_UnlockSurface(image);

	freeUint8Array(tabImg, image->w);

	displayImg(image);  
  return 0;
}
