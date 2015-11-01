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
      break;
    case 3:
      break;
    case 4:
      img = malloc(sizeof(struct ImgVal));
      loadImg(img);
      printf("load_img OK");
      struct StrongClassifier *sc = malloc(sizeof(struct StrongClassifier));
      Boost(sc,img,6400,2400);
      free(img);
      break;
    default:
      break;
  }
  return 0;
}

void loadImg(struct ImgVal *img)
{
    SDL_Surface *image;
    char s[] = "./src/face/face00000.pgm";
    for(int i = 1;i<2401;i++)
    {
        s[19] = i % 10 + '0';
        s[18] = i/10 % 10 + '0';
        s[17] = i/100 % 10 + '0';
        s[16] = i/1000 % 10 + '0';
        image = loadimg(s);
	    int **tabImg = imgToArray(image);       
        integralImg(tabImg, image->w, image->h);
        for(int x = 0;x<19;x++)
        {
            for(int y = 0;y<19;y++)
            {
                img->wc[i-1].integ[x][y] = tabImg[x][y];
                printf("%d",img->wc[i-1].integ[x][y]);
            }   
        }
        
    }
    char n[] = "./src/nface/negat0000.pgm";
    for(int j = 2401;j<6401;j++)
    {
        n[20] = (j-2400) % 10 +'0';
        n[19] = (j-2400)/10 % 10 +'0';
        n[18] = (j-2400)/100 % 10 + '0';
        n[17] = (j-2400)/1000 % 10 + '0';
        image = loadimg(n);
	    int **tabImg = imgToArray(image);       
        integralImg(tabImg, image->w, image->h);
        for(int x = 0;x<19;x++)
        {
            for(int y = 0;y<19;y++)
                img->wc[j-1].integ[x][y] = tabImg[x][y];
        }
    }

}
