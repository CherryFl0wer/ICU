#ifndef _ADABOOST_H_
#define _ADABOOST_H_

#include<stdlib.h>
#include<stdio.h>
#include"HaarFeatures.h"


typedef int subimg[24][24];
struct WeakClassifier { 
    struct HaarFeat* feature;
    int threshold;
    subimg x;
    int polarity;
};

struct StrongClassifier {
    struct WeakClassifier wc[1000]; /* 1000 = number of tested image */
    int alpha[1000]; /* same as above */
};

void Boost(struct StrongClassifier *sc, int nbImg, int pos);

#endif
