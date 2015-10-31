#ifndef _ADABOOST_H_
#define _ADABOOST_H_

#include<stdlib.h>
#include<stdio.h>
#include"HaarFeatures.h"



struct WeakClassifier { 
    struct HaarFeat* feature;
    int w;
    int integ[24][24];
    int polarity;
};

struct ImgVal {
    struct WeakClassifier wc[1000];// 1000 = number of image to test
    int theta;
};



struct StrongClassifier {
    struct WeakClassifier wc[200]; /* 200 = number of weakclassifier needed */
    int alpha[200]; /* same as above */
};

void Boost(struct StrongClassifier *sc,struct ImgVal *img, int nbImg, int pos);

#endif
