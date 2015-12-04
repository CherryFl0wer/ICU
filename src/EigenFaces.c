# include "EigenFaces.h"

double** declare_set(size_t nbImg, char** pathListImg) {
  double** set = malloc(nbImg * sizeof(double*));

  for(size_t i = 0; i < nbImg; i++) {
    printf("loading : %s \n", pathListImg[i]);
    SDL_Surface* img = loadimg(pathListImg[i]);
    if(img == NULL) { 
      printf("Error img %s not loaded\n", pathListImg[i]);
      exit(1);
    }
    
    set[i] = malloc(sizeof(double) * SIZE_IMG);
    if(set[i] == NULL) 
      exit(1); // error not enough memory

    set[i] = flatten(img, SIZE_IMG_WIDTH, SIZE_IMG_HEIGHT);
  }

  return set;
}

void free_mat(double** mat, size_t row) {
  for(size_t i = 0; i < row; i++) 
   free(mat[i]); 

  free(mat);
}


// The matrix will be a vector of size m*n containing greyscale value 
double* flatten(SDL_Surface* image, size_t width, size_t height) {
  size_t newsize = width * height;
  double* mat = calloc(newsize, sizeof(double));
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
double mean_img(double** set, size_t nbImg ) {
  double* avgvect = calloc(SIZE_IMG, sizeof(double));
 
  for(size_t i = 0; i < SIZE_IMG; i++) {
    for(size_t j = 0; j < nbImg; j++) 
      avgvect[i] += set[j][i];
  }
  double sum = 0;
  for(size_t i = 0; i < SIZE_IMG; i++) 
    sum += avgvect[i] / nbImg;

  return sum;
}


void matSubVal(double** mat, size_t nMat, size_t mMat, double eps) {
  for(size_t i = 0; i < nMat; i++)  // nbImg
    for(size_t j = 0; j < mMat; j++)  // SIZE_IMG
      mat[i][j] -= eps;
}

double** matSub(double** mat1, double** mat2, size_t nMat, size_t mMat) {
  double** mat = malloc(nMat * sizeof(double*));
  for(size_t i = 0; i < nMat; i++) {
    mat[i] = calloc(mMat, sizeof(double));
    for(size_t j = 0; j < mMat; j++) {
      mat[i][j] = mat1[i][j] - mat2[i][j];
    }
  }

  return (mat == NULL) ? NULL : mat;
}

void matAddVal(double** mat, size_t nMat, size_t mMat, double eps) {
  for(size_t i = 0; i < nMat; i++)  
    for(size_t j = 0; j < mMat; j++) 
      mat[i][j] += eps;
}


double** matAdd(double** mat1, double** mat2, size_t nMat, size_t mMat) {
  double** mat = malloc(nMat * sizeof(double*));
  for(size_t i = 0; i < nMat; i++) {
    mat[i] = calloc(mMat, sizeof(double));
    for(size_t j = 0; j < mMat; j++) {
      mat[i][j] = mat1[i][j] + mat2[i][j];
    }
  }

  return (mat == NULL) ? NULL : mat;
}

double** matMul(double** A, double** B, size_t nA, size_t nm, size_t mB) { 
  double** mat = malloc(nA * mB * sizeof(double*));
  for(size_t i = 0; i < nA; i++) {
    mat[i] = calloc(mB, sizeof(double));
    for(size_t j = 0; j < mB; j++) {
      for(size_t k = 0; k < nm; k++) { 
        mat[i][j] += A[i][k] * B[k][j];
      } 
    }
  }

  return (mat == NULL) ? NULL : mat;
}

void matMulVal(double** mat, size_t nA, size_t mA, double eps) {  
  for(size_t i = 0; i < nA; i++) { 
    for(size_t j = 0; j < mA; j++) { 
        mat[i][j] *= eps;
    }
  }
}



double**  transposed(double** mat, size_t nMat, size_t mMat) {
  double** mat_T = malloc(nMat * sizeof(double*));
  for(size_t i = 0; i < nMat; i++) { // Size_IMG
     mat_T[i] = calloc(mMat, sizeof(double));
     for(size_t j = 0; j < mMat; j++) // nbImg
       mat_T[i][j] = mat[j][i];
  }

  return (mat_T == NULL) ? NULL : mat_T;
}




double** covariance(double** set, double** transposedSet, size_t nbImg) {
  // Matrix of M x M where M = nb Img
  // and not N^2 x N^2 because too large 
  // C = A^t * A and not C = A*A^t 

  double** covMatrix =  matMul(set, transposedImg, nbImg, nbImg, nbImg, nbImg);
  return covMatrix;
}



double* proj(double* v1, double* v2, size_t col) {
  double* vect = calloc(col, sizeof(double));
  for(size_t i = 0; i < col; i++) {
    vect[i] = v1[i] * v2[i];
    vect[i] *= v1[i];
  }
  
  return (vect == NULL) ? NULL : vect;
}

double mat_norm(double* vect, size_t col) {
  double norm = 0.0;
  for(size_t i = 0; i < col; i++) {
    norm += vect[i] * vect[i];
  }

  return sqrt(norm);
}
/*

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
  

  double** setOfImg = declare_set(NB_IMG_TEST, pathListImg);

  for(size_t i = 0; i < 1; i++) {
    printf("[ ");
    for(size_t j = 0; j < SIZE_IMG; j++) {
      printf("%d ",setOfImg[0][j]);
    }
    printf(" ]");
  }

  double** setOfImgT = transposed(setOfImg, NB_IMG_TEST);
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
*/
