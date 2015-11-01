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
void loadImg();

int main(int argc, const char* argv[])
{
  loadImg();
  SDL_Surface  *image;	

  if(argc != 2) return 1;
	
	SDLInit();

  image = loadimg(argv[1]);

	// _____________________ //
	
	SDL_LockSurface(image);

 	imgToGreyScale(image);
	normalize(image);
	equalize(image);
	uint32_t **tabImg = imgToArray(image);
	integralImg(tabImg, image->w, image->h);

	SDL_UnlockSurface(image);

	freeUint8Array(tabImg, image->w);

	displayImg(image);  
  return 0;
}

void loadImg(struct ImgVal *img)
{
    int pos = 2400;
    char s[14] = "face00000.pgm";
    for(int i = 1;i<2401;i++)
    {
        s[8] = i % 10 + '0';
        s[7] = i/10 % 10 + '0';
        s[6] = i/100 % 10 + '0';
        s[5] = i/1000 % 10 + '0';
        
    }
}
