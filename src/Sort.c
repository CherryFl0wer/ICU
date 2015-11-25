#include<stdio.h>
#include<stdlib.h>

#include "HaarFeatures.h"
#include "Adaboost.h"
int compare(const void *p1, const void *p2)
{
    struct WeakClassifier *s1 = (struct WeakClassifier*)p1;
    struct WeakClassifier *s2 = (struct WeakClassifier*)p2;
    return (s1->val - s2->val);
}

struct ImgVal* sort(struct ImgVal *img)
{
    struct ImgVal *res = malloc(sizeof(struct ImgVal));
    for(int i = 0;i<6400;i++)
      res->wc[i] = img->wc[i];
    qsort(res->wc, 6400, sizeof(struct WeakClassifier), compare);
    return res;
}
