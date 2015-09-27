#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char** argv) { 
  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stdout, "Echec de l'init de la sdl (%s)\n", SDL_GetError());
    return -1;
  }
  
  SDL_Window* win = NULL;
  win = SDL_CreateWindow("Window sdl", SDL_WINDOWPOS_UNDEFINED, 
				       SDL_WINDOWPOS_UNDEFINED,
				       640,
				       480,
				       SDL_WINDOW_SHOWN);

  if(win) { 
    SDL_Delay(3000);
    SDL_DestroyWindow(win);
  } else {
   fprintf(stderr, "Erreur création de la fenetre (%s) \n", SDL_GetError());
  }
  
  SDL_Quit();

  return 0;
}
