#ifndef EIGENFACES_HEADER_
#define EIGENFACES_HEADER_
# include <stdlib.h>
# include <SDL.h>
# include <SDL_image.h>
# include <string.h>
# include <stdint.h>
# include "SDLPixel.h"

# define NB_IMG_TEST 20
# define SIZE_IMG_HEIGHT 19
# define SIZE_IMG_WIDTH  19
# define SIZE_IMG        (SIZE_IMG_HEIGHT * SIZE_IMG_WIDTH)

int** declare_set(size_t nbImg, char** pathListImg);
void destroy_set(int** set, size_t nbImg);
int* flatten(SDL_Surface* image, size_t width, size_t height);
double mean(int** set, size_t nbImg);
void rm_common_data(int** set, size_t nbImg, double meanEps);
int** transposed(int** set, size_t nbImg);
#endif
