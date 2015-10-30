# ifndef _TREATMENT_H_
# define _TREATMENT_H_

#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<SDL.h>
#include<SDL_image.h>

void normalize(SDL_Surface *img);

void equalize(SDL_Surface *img);

void segIm(SDL_Surface *img);


void face(int **arr,int *x, int *y, int *h,int weight, int height);

int** imgToArrayFace(SDL_Surface* img);

void square(SDL_Surface *img,int x,int y,int w);

#endif
