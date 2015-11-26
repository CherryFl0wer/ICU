#include "ArrayUtils.h"
#include "EigenFaces.h"

// The matrix will be a vector of size m*n containing greyscale value 
int* flatten(SDL_Surface* imggrey, size_t width, size_t height) {
  size_t newsize = width * height;
  int* mat = calloc(newsize * sizeof(int));
  uint8_t r, g, b;
  
  for(size_t i = 0; i < width; i++) {
    for(size_t j = 0; j < height; j++) {
      SDL_GetRGB(getpixel(imggrey, i, j) imggrey->format, &r, &g, &b);
      mat[i * height + j] = r;
    }
  }
  return mat;
}




