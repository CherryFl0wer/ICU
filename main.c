#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <SDL_image.h>

// Personal Headers

#include "./src/IntegralImage.h"
#include "./src/ArrayUtils.h"
#include "./src/SDLPixel.h"

int main(int argc, const char* argv[])
{
  SDL_Surface  *image;	

  if(argc != 2) return 1;
	
	SDLInit();

  image = loadimg(argv[1]);

	// _____________________ //


	uint8_t **tabImg = Uint8Array(image->w, image->h);	
	
	SDL_LockSurface(image);

	uint32_t **img_array = imgToArray(image);

 	imgToGreyScale(image, img_array, tabImg);

	integralImg(tabImg, image->w, image->h);

	SDL_UnlockSurface(image);

	freeUint8Array(tabImg, image->w);
	freeImgArray(img_array, image->w);

	displayImg(image);  
  return 0;
}
