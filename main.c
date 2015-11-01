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
//#include "./src/Adaboost.h"

void loadImg();

int main(int argc, const char* argv[])
{
  loadImg();
  SDL_Surface  *image;	

  if(argc != 2) return 1;
	
	SDLInit();

  image = loadimg(argv[1]);

	// _____________________ //
	
	SDL_LockSurface(image);

 	imgToGreyScale(image);
	normalize(image);
	equalize(image);
	int **tabImg = imgToArray(image);
	integralImg(tabImg, image->w, image->h);

	SDL_UnlockSurface(image);

	freeUint8Array(tabImg, image->w);

	displayImg(image);  
  return 0;
}

void loadImg(struct ImgVal *img)
{
    int pos = 2400;
    SDL_Surface *image;
    char s[] = "./src/face/face00000.pgm";
    for(int i = 1;i<2401;i++)
    {
        s[19] = i % 10 + '0';
        s[18] = i/10 % 10 + '0';
        s[17] = i/100 % 10 + '0';
        s[16] = i/1000 % 10 + '0';
        image = loadimg(s);
        printf("2\n");
	    int **tabImg = imgToArray(image);
	    int arr[19][19];
        for(int i = 0;i<19;i++)
        {
            for(int j = 0;j<19;j++)
                arr[i][j] = tabImg[i][j];
        }
        integralImg(tabImg, image->w, image->h);
        printf("OK\n");
        struct HaarFeat *vect = malloc(2*sizeof(struct HaarFeat));
        MakeVectWithFeat(vect,arr);
    }
}
