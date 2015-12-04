# ifndef DETECTION_H_
# define DETECTION_H_

# include <stdlib.h>
# include <stdio.h>
# include "Adaboost.h"
struct Rect{
  int x,y,w,h;
};
void detect(struct Rect rects[50],struct StrongClassifier *sc, int **array,int w_max,int h_max);

# endif
