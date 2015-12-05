#ifndef EIGENFACES_HEADER_
#define EIGENFACES_HEADER_
# include <stdlib.h>
# include <SDL.h>
# include <SDL_image.h>
# include <string.h>
# include <stdint.h>
# include "SDLPixel.h"
# include <math.h>

# define NB_IMG_TEST 20
# define SIZE_IMG_HEIGHT 19
# define SIZE_IMG_WIDTH  19
# define SIZE_IMG        (SIZE_IMG_HEIGHT * SIZE_IMG_WIDTH)

double** declare_set(size_t nbImg, char** pathListImg);
void free_mat(double** mat, size_t row);
double* flatten(SDL_Surface* image, size_t width, size_t height);
double mean_img(double** set, size_t nbImg);
void matSubVal(double** mat, size_t nMat, size_t mMat, double eps);
double** matSub(double** mat1, double** mat2, size_t nMat, size_t mMat);
void matAddVal(double** mat, size_t nMat, size_t mMat, double eps);
double** matAdd(double** mat1, double** mat2, size_t nMat, size_t mMat);
double** matMul(double** A, double** B, size_t nA, size_t nm, size_t mB);
void matMulVal(double** mat, size_t nMat, size_t mMat, double eps);
double** transposed(double** mat,size_t nMat,size_t mMat);
double** covariance(double** set, double** transposedSet, size_t nbImg);
double* vectDiv(double* v1, double v2,size_t nbImg);
double* vectSub(double* v1, double* v2,size_t nbImg);
double* proj(double* v1, double* v2, size_t col);
double mat_norm(double* vect, size_t col);
double** compute_Q(double** A,size_t nbImg);

double** compute_R(double** A,double **Q,size_t nbImg, size_t size);

#endif
