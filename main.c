#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL.h>
#include <SDL_image.h>
#include <gtk/gtk.h>

// Personal Headers
#include "./src/IntegralImage.h"

int main(int argc, const char* argv[])
{

  SDL_Surface *screen, *image;
  SDL_Event event;
  bool done = false;

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
	
	SDL_LockSurface(image);
 	integralimage(image);
	SDL_UnlockSurface(image);

  screen = SDL_SetVideoMode(image->w, image->h, image->format->BitsPerPixel,
    SDL_ANYFORMAT);

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
        done = true;
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
