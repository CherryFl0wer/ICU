# ifndef _TREATMENT_H_
# define _TREATMENT_H_

#include<stdlib.h>
#include<stdio.h>
#include<SDL.h>


void normalize(SDL_Surface *img);

void equalize(SDL_Surface *img);

void image_to_grey(SDL_Surface *img);


#endif
