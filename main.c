#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <SDL_image.h>

// Personal Headers

#include "./src/IntegralImage.h"
#include "./src/ArrayUtils.h"
#include "./src/SDLPixel.h"
#include "./src/Treatment.h"
#include "./src/HaarFeatures.h"
#include "./src/Adaboost.h"
#include "./db/db.h"
#include "./src/Training.h"
#include "./src/Detection.h"

void loadImg(struct ImgVal *img);

int main()
{
  printf("Tapez l'étape voulue : \n");
  printf("-1 : pré-traitement de l'image\n");
  printf("-2 : reconnaissance visage\n");
  printf("-3 : accès à la base de donnée\n");
  printf("-4 : création du strongclassifier\n");
  int input = 0;
  if(!(scanf("%d",&(input))))
  {
    printf("error d'acquisition");
    return 0;
  }
  SDL_Surface  *image;  
  struct ImgVal *img;
  struct StrongClassifier *strong;
  switch(input)
  {
    case 1:
      

      SDLInit();
      printf("entrez le chemin d'une image\n");
      char path[255];
      if(!(scanf("%s",path)))
      {
        printf("erreur d'acquisition");
        return 0;
      }      
      image = loadimg(path);
      
	  // _____________________ //
	  displayImg(image);
      segIm(image);
      displayImg(image);
      int **array = imgToArrayFace(image);
      integralImg(array,image->w,image->h);
      int *x = malloc(sizeof(int)),*y = malloc(sizeof(int)),*w = malloc(sizeof(int));
      face(array,x,y,w,image->w,image->h);
      square(image,*x,*y,*w);
      displayImg(image);
      image = loadimg(path);
      displayImg(image);
 	  imgToGreyScale(image);
      displayImg(image);
	  normalize(image);
      displayImg(image);
	  equalize(image);
      displayImg(image);
	  SDL_LockSurface(image);
      int **tabImg = imgToArray(image);
	  integralImg(tabImg, image->w, image->h);

	  SDL_UnlockSurface(image);

	  freeUint8Array(tabImg, image->w);

      SDL_FreeSurface(image);
      SDL_Quit();
      break;
    case 2:
      strong = malloc(sizeof(struct StrongClassifier));
      get_training(strong);
      SDLInit();
      printf("entrez le chemin d'une image\n");
      char path2[255];
      if(!(scanf("%s",path2)))
      {
        printf("erreur d'acquisition");
        return 0;
      }      
      image = loadimg(path2);
      
	  // _____________________ //
      displayImg(image);
	    imgToGreyScale(image);
	    normalize(image);
	    equalize(image);
	    SDL_LockSurface(image);
      int **tabImg2 = imgToArray(image);
	    integralImg(tabImg2, image->w, image->h);
      struct Rect rects[250];
      detect(rects,strong,tabImg2,image->w,image->h);
      int cpt = 0;
      while(cpt < 250 && rects[cpt].x >= 0)
      {
        square(image,rects[cpt].x,rects[cpt].y,rects[cpt].w);
        cpt++;
      }
      printf("number of faces : %d\n",cpt);

	    SDL_UnlockSurface(image);
      displayImg(image);

      

      SDL_FreeSurface(image);
      SDL_Quit();
      free(strong);
      break;
    case 3:
      ManageDatabase();
      break;
    case 4:
      img = malloc(sizeof(struct ImgVal));
      loadImg(img);
      struct StrongClassifier *sc = malloc(sizeof(struct StrongClassifier));
      Boost(sc,img,6400,2400);
      free(img);
      free(sc);
      break;
    default:
      break;
    

  }
  return 0;
}

void loadImg(struct ImgVal *img)
{
    SDL_Surface *image;
    for(int i = 1;i<2401;i++)
    {
        char path[30];
        snprintf(path, 30, "./src/face/face%d.pgm", i);
        image = loadimg(path);
	      int **tabImg = imgToArray(image);       
        integralImg(tabImg, image->w, image->h);
        for(int x = 0;x<19;x++)
        {
            for(int y = 0;y<19;y++)
            {
                img->wc[i-1].integ[x][y] = tabImg[x][y];
            }   
        }
        
    }
 
    for(int j = 2401;j<6401;j++)
    {
      char path[30];
      snprintf(path, 30, "./src/nface/negat%d.pgm", j);
      image = loadimg(path);
	    int **tabImg = imgToArray(image);       
        integralImg(tabImg, image->w, image->h);
        for(int x = 0;x<19;x++)
        {
            for(int y = 0;y<19;y++)
                img->wc[j-1].integ[x][y] = tabImg[x][y];
        }
    }
    printf("Initialsation des images OK\n");

}
