#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <SDL_image.h>

// Personal Headers

#include "./src/IntegralImage.h"
#include "./src/ArrayUtils.h"


int main(int argc, const char* argv[])
{
  SDL_Surface *screen, *image;
  SDL_Event event;
	int done = 0;

  if(argc != 2) return 1;

  if(SDL_Init(SDL_INIT_VIDEO) == -1) {
    printf("SDL_Init: %s\n", SDL_GetError());
    return 1;
  }

  image = IMG_Load(argv[1]);
  if(!image) {
    printf("Image failed to load %s \n ", IMG_GetError());
    SDL_Quit();
    return 1;
  }
	// _____________________ //

	uint8_t **tabImg = allocMemArr(image->w, image->h);	
	
	SDL_LockSurface(image);

 	imgToGreyScale(image, tabImg);
	//print_array2D(tabImg, 0, image->w, 0, image->h, 1);	
	integralImg(tabImg, image->w, image->h);

	SDL_UnlockSurface(image);

	freeMemArr(tabImg, image->w);
  
	screen = SDL_SetVideoMode(image->w, image->h, image->format->BitsPerPixel,
    SDL_ANYFORMAT);
	
	// ____________________ //
  if(!screen) {
    printf("SDL_SetVideoMode : %s \n", SDL_GetError());
    SDL_FreeSurface(image);
    SDL_Quit();
    return 1;
  }

  SDL_WM_SetCaption(argv[1], argv[1]);

  SDL_BlitSurface(image, 0, screen, 0);
  SDL_Flip(screen);

  while(!done && SDL_WaitEvent(&event) != -1) {
    switch(event.type) {
      case SDL_KEYDOWN:
      case SDL_QUIT:
        done = 1;
        break;
      case SDL_VIDEOEXPOSE:
        SDL_BlitSurface(image, 0, screen, 0);
        SDL_Flip(screen);
        break;
      default:
        break;
    }
  }

  SDL_FreeSurface(image);
  SDL_Quit(); 

  return 0;
}
