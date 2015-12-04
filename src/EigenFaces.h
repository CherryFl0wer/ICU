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

double** declare_set(size_t nbImg, char** pathListImg);
void destroy_set(double** set, size_t nbImg);
double* flatten(SDL_Surface* image, size_t width, size_t height);
double mean(double** set, size_t nbImg);
void rm_common_data(double** set, size_t nbImg, double meanEps);
double** transposed(double** set, size_t nbImg);
double** covariance(double** set, double** transposedSet, size_t nbImg);
#endif
