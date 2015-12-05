# include "EigenFaces.h"

void print_matrix(double** mat, size_t row, size_t col) {
  printf(" ------ Matrice [%zu x %zu] ------- \n\n", row, col);
  printf(" [\n");
  for(size_t j = 0; j < row; j++) { 
    printf(" ");
    for(size_t i = 0; i < col; i++) {
      printf(" %f ", mat[j][i]);
    }
    printf("\n");
  }
  printf(" ] \n");
}

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
  
  return set; //transposed(set, nbImg, SIZE_IMG);
}

void free_mat(double** mat, size_t row) {
  for(size_t i = 0; i < row; i++) 
   free(mat[i]); 

  free(mat);
}
void free_mat_char(char** mat, size_t row) {
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
 
  for(size_t i = 0; i < nbImg; i++) {
    for(size_t j = 0; j < SIZE_IMG; j++) 
      avgvect[i] += set[i][j];
  }
  double sum = 0;
  for(size_t i = 0; i < nbImg; i++) 
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
  double** mat = malloc(nA * sizeof(double*));
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

double** mulR(double** A, double** B, size_t nA, size_t nm, size_t mB) { 
  double** mat = malloc(nA * sizeof(double*));
  for(size_t i = 0; i < nA; i++) {
    mat[i] = calloc(mB, sizeof(double));
    for(size_t j = 0; j < mB; j++) {
      for(size_t k = 0; k < nm; k++) { 
        mat[i][j] += A[k][i] * B[j][k];
        //printf("(i=%zu,j=%zu,k=%zu) %f = %f * %f \n", i, j, k, mat[i][j], A[i][k], B[k][j]);
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




double** covariance(double** set, double** transposedSet, size_t nbImg, size_t size) {
  // Matrix of M x M where M = nb Img
  // and not N^2 x N^2 because too large 
  // C = A^t * A and not C = A*A^t 

  double** covMatrix =  matMul(set, transposedSet, nbImg, size, nbImg);
  return covMatrix;
}



double* proj(double* v1, double* v2, size_t col) {
  double* vect = calloc(col, sizeof(double));
  double p = 0;
  for(size_t i = 0; i < col; i++) {
    p += v1[i] * v2[i];
  }
  for(size_t i = 0;i<col;i++)
  {
    vect[i] = p * v1[i];
  }
  return (vect == NULL) ? NULL : vect;
}

double* vectDiv(double* v1,double v2,size_t col){
  double* vect = calloc(col,sizeof(double));
  for(size_t i = 0; i<col;i++)
    vect[i] = v1[i]/v2;
  return vect;
}

double* vectSub(double* v1, double* v2,size_t col){
  double* vect = calloc(col,sizeof(double));
  for(size_t i = 0; i<col;i++)
    vect[i] = v1[i]-v2[i];
  return vect;
}

double** compute_Q(double** A,size_t nbImg, size_t size)
{
  double** Q = malloc(nbImg * sizeof(double*));
  for(size_t i = 0; i < nbImg; i++)
    Q[i] = calloc(size, sizeof(double));
  
  Q[0] = vectDiv(A[0],mat_norm(A[0],size),size);
  for(size_t i = 1;i<nbImg;i++)
  {
    Q[i]=A[i];
    for(size_t j = i-1;j+1>=1;j--)
      Q[i] = vectSub(Q[i],proj(Q[j],A[i],size),size);
    Q[i]=vectDiv(Q[i],mat_norm(Q[i],size),size);
  }

  return Q;
}

double** compute_R(double** A, double** Q, size_t nbImg, size_t size)
{
  double** trans_Q = transposed(Q,size,nbImg);
  print_matrix(trans_Q, 3, 2);
  double** R = mulR(trans_Q,A, nbImg,size,nbImg);
  return R;
}  




  

double mat_norm(double* vect, size_t col) {
  double norm = 0.0;
  for(size_t i = 0; i < col; i++) {
    norm += pow(vect[i],2);
  }

  return sqrt(norm);
}

void display_Q(double** Q,size_t nbImg, size_t size,size_t cote,SDL_Surface *img)
{
  Uint32 pix = 0;
  Uint8 r = 0;
  for(size_t i = 0;i<nbImg;i++)
  {
    for(size_t j = 0;j<size;j++)
    {
      r = Q[i][j];
      pix = SDL_MapRGB(img->format,r,r,r);
      putpixel(img,j/cote,j%cote,pix);
    }
    displayImg(img);
  }

}

double** compute_U(double** A,double** R,size_t nbImg,size_t size)
{
  double** U = malloc(nbImg * sizeof(double*));
  for(size_t i = 0; i < nbImg; i++)
    U[i] = calloc(size, sizeof(double));
  for(size_t i = 0 ; i<nbImg;i++)
  {
    for(size_t j = 0; j<size;j++)
      U[i][j] = R[i][i] * A[i][j];
    printf("%f\n",R[i][i]);
  }   
  return U;
}

int main() {
  // Get all samples of images 
  // By   loading all the files
  char** pathListImg = malloc(NB_IMG_TEST * sizeof(char*));

  // Fill the path of img
 
  for(size_t i = 1; i <= NB_IMG_TEST; i++) {
    pathListImg[i-1] = calloc(30,sizeof(char));
    char path[30]; 
    snprintf(path, 30, "./Reco/%zu.jpeg", i);
    strcpy(pathListImg[i-1], path);
  }
 /* 
  // Step 1 : Flatten img
  double** set = declare_set(NB_IMG_TEST, pathListImg);
  // Step 2 : Average Vector Calcul
  double eps = mean_img(set, NB_IMG_TEST);
  // Step 3 : Substract A.V with the pixel
  matSubVal(set, NB_IMG_TEST, SIZE_IMG,eps);
  // Step 4 : Covariance
  double** setT = transposed(set,SIZE_IMG, NB_IMG_TEST);
  double** covSet = covariance(set, setT, NB_IMG_TEST, SIZE_IMG);
  double** Q = compute_Q(covSet, NB_IMG_TEST);
  double** R = compute_R(covSet, Q, NB_IMG_TEST, NB_IMG_TEST);
  double** U = compute_U(set,R,NB_IMG_TEST,SIZE_IMG);
*/
//  SDL_Surface *img = loadimg("./Reco/1.jpeg");
 // display_Q(U,NB_IMG_TEST,SIZE_IMG,SIZE_IMG_WIDTH,img);
  
  // Matrice Example
  double** matrice = malloc(2 * sizeof(double*));
  for(size_t i = 0; i < 2; i++) {
    matrice[i] = calloc(3, sizeof(double));
  }
  
  matrice[0][0] = 2;
  matrice[0][1] = 2;
  matrice[0][2] = 1;
  matrice[1][0] = 1;
  matrice[1][1] = 1;
  matrice[1][2] = 5;
 
  //matrice = transposed(matrice, 3, 3);

  print_matrix(matrice, 2, 3);
  double** Qmatrice = compute_Q(matrice, 2, 3);
  print_matrix(Qmatrice, 2, 3);
  double** Rmatrice = compute_R(matrice, Qmatrice, 2, 3);
  print_matrix(Rmatrice, 2, 2);
  free_mat(matrice, 3);
  free_mat_char(pathListImg, NB_IMG_TEST);
 /* free_mat(set, NB_IMG_TEST);
  free_mat(setT, SIZE_IMG);
  free_mat(covSet, NB_IMG_TEST);
 // SDL_FreeSurface(img);
  free_mat(Q, NB_IMG_TEST);
  free_mat(R, NB_IMG_TEST);
  free_mat(U, NB_IMG_TEST);
 */ 
  return 0;
}
