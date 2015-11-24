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

void sort(struct ImgVal *img)
{

    qsort(img->wc, 6400, sizeof(struct WeakClassifier), compare);

}
