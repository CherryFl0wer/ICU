#include <stdio.h>
#include <stdlib.h>

#include "Detection.h"
#include "Adaboost.h"
#include "HaarFeatures.h"

void detect(struct Rect rects[250],struct StrongClassifier *sc,int **array,int w_max,int h_max)
{
  for(int i = 0;i<50;i++)
    rects[i].x = -1;
  struct Rect *squ = malloc(sizeof(struct Rect));
  squ->x = 1;
  squ->y = 1;
  squ->w = 19;
  squ->h = 19;
  int squw = 20;
  int squh = 20;
  int count_squ = 0;
  double som_alpha, som;
  while(squ->x +squw < w_max && squ->y + squh < h_max)
  {
    while(squ->y + squh < h_max)
    {
      while(squ->x + squw < w_max)
      {
        som = 0;
        som_alpha = 0;
        for(int i = 0;i < 200;i++)
        {
          struct HaarFeat *haar = malloc(sizeof(struct HaarFeat));
          haar->x = squ->x + (sc->wc[i].feature->x * squ->w)/19;
          haar->y = squ->y + (sc->wc[i].feature->y * squ->h)/19;
          haar->w = (sc->wc[i].feature->w * squ->w)/19;
          haar->h = (sc->wc[i].feature->h * squ->h)/19;
          switch(sc->wc[i].feature->feat)
          {
            case 1 : 
              ValFeatA_det(haar,array);
              break;
            case 2 : 
              ValFeatB_det(haar,array);
              break;
            case 3 : 
              ValFeatC_det(haar,array);
              break;
            case 4 : 
              ValFeatD_det(haar,array);
              break;
            case 5 : 
              ValFeatE_det(haar,array);
              break;
            default :
              break;
          }
          if(haar->val*sc->wc[i].polarity <=  sc->wc[i].threshold * sc->wc[i].polarity)
            som += sc->alpha[i];
          som_alpha += sc->alpha[i];
          free(haar);
        }
        //printf("%f    %f\n",som,som_alpha);
        if(count_squ < 250 &&som >= 0.675 * som_alpha)
        {
          rects[count_squ].x = squ->x;
          rects[count_squ].y = squ->y;
          rects[count_squ].w = squ->w;
          rects[count_squ].h = squ->y;
          count_squ++;
        }
        squ->x++;
      }
      squ->x = 0;
      squ->y++;
    }
    squ->x = 0;
    squ->y = 0;
    squ->w *= 1.25;
    squ->h *= 1.25;
    squw *= 1.25;
    squh *= 1.25;
  }
  free(squ);
}
