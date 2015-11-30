# include "EigenFaces.h"

int** declare_set(size_t nbImg, char** pathListImg) {
  int** set = malloc(nbImg * sizeof(int*));

  for(size_t i = 0; i < nbImg; i++) {
    printf("loading : %s \n", pathListImg[i]);
    SDL_Surface* img = loadimg(pathListImg[i]);
    if(img == NULL) { 
      printf("Error img %s not loaded\n", pathListImg[i]);
      exit(1);
    }
    
    set[i] = malloc(sizeof(int) * SIZE_IMG);
    if(set[i] == NULL) 
      exit(1); // error not enough memory

    set[i] = flatten(img, SIZE_IMG_WIDTH, SIZE_IMG_HEIGHT);
  }

  return set;
}

void destroy_set(int** set, size_t nbImg) {
  for(size_t i = 0; i < nbImg; i++) 
   free(set[i]); 

  free(set);
}


// The matrix will be a vector of size m*n containing greyscale value 
int* flatten(SDL_Surface* image, size_t width, size_t height) {
  size_t newsize = width * height;
  int* mat = calloc(newsize, sizeof(int));
  uint8_t r;
  
  for(size_t i = 0; i < width; i++) {
    for(size_t j = 0; j < height; j++) {
      SDL_GetRGB(getpixel(image, i, j), image->format, &r, &r, &r);
      mat[i * height + j] = r;
    }
  }
  return mat;
}


// Mean Image is going to calcul the average of each pixel
double mean_img(int** set, size_t nbImg ) {
  int* avgvect = calloc(SIZE_IMG, sizeof(int));
 
  for(size_t i = 0; i < SIZE_IMG; i++) {
    for(size_t j = 0; j < nbImg; j++) 
      avgvect[i] += set[j][i];
  }
  double sum = 0;
  for(size_t i = 0; i < SIZE_IMG; i++) 
    sum += avgvect[i] / nbImg;

  return sum;
}


void rm_common_data(int** set, size_t nbImg, double meanEps) {
  for(size_t i = 0; i < nbImg; i++) 
    for(size_t j = 0; j < SIZE_IMG; j++) 
      set[i][j] -= meanEps;
}

int**  transposed(int** set, size_t nbImg) {
  int** nSet = malloc(SIZE_IMG * sizeof(int*));
  for(size_t i = 0; i < SIZE_IMG; i++) {
     nSet[i] = calloc(nbImg, sizeof(int));
     for(size_t j = 0; j < nbImg; j++)
       nSet[i][j] = set[j][i];
  }

  return (nSet == NULL) ? NULL : nSet;
}

int** covariance(int** set, int** transposedSet, size_t nbImg) {
  // Matrix of M x M where M = nb Img
  // and not N^2 x N^2 because too large 
  // C = A^t * A and not C = A*A^t 

  int** covMatrix = malloc(nbImg * sizeof(int*));
  for(size_t i = 0; i < nbImg; i++) {
    covMatrix[i] = calloc(nbImg, sizeof(int));
    for(size_t j = 0; j < nbImg; j++) {
      for(size_t k = 0; k < nbImg; k++) { 
        covMatrix[i][j] += set[i][k] * transposedSet[k][j];
      } 
    }
  }

  return (covMatrix == NULL) ? NULL : covMatrix;
}



int main() {
  // Get all samples of images 
  // By   loading all the files
  char** pathListImg = malloc(NB_IMG_TEST * sizeof(char*));

  // Fill the path of img
 
  for(size_t i = 1; i <= NB_IMG_TEST; i++) {
    pathListImg[i-1] = calloc(30,sizeof(char));
    char path[30]; 
    snprintf(path, 30, "./src/face/face%zu.pgm", i);
    strcpy(pathListImg[i-1], path);
  }
  

  int** setOfImg = declare_set(NB_IMG_TEST, pathListImg);

  for(size_t i = 0; i < 1; i++) {
    printf("[ ");
    for(size_t j = 0; j < SIZE_IMG; j++) {
      printf("%d ",setOfImg[0][j]);
    }
    printf(" ]");
  }
  int** setOfImgT = transposed(setOfImg, NB_IMG_TEST);
  printf("\n\n\n [ ");
  for(size_t i = 0; i < SIZE_IMG; i++) { 
    printf("%d ", setOfImgT[i][0]);
  }
  printf("\n ]");


  // clear pathListImg
  for(size_t i = 0; i < NB_IMG_TEST; i++) 
    free(pathListImg[i]);
  free(pathListImg);
  
  for(size_t i = 0; i < SIZE_IMG; i++) 
    free(setOfImgT[i]);
  free(setOfImgT);

  destroy_set(setOfImg, NB_IMG_TEST);
  return 0;
}
