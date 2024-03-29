#ifndef _ADABOOST_H_
#define _ADABOOST_H_

#include<stdlib.h>
#include<stdio.h>
#include<math.h> 
#include"HaarFeatures.h"

#define NBIMG 1000


struct WeakClassifier { 
    struct HaarFeat* feature;
    int val;
    double w;
    int threshold;
    int integ[19][19];
    int polarity;
};

struct ImgVal {
    struct WeakClassifier wc[6400];// 1000 = number of image to test
    int theta;
    int T;
    int M;
    double e;
};


struct StrongClassifier {
    struct WeakClassifier wc[200]; /* 190 = number of weakclassifier needed */
    double alpha[200]; /* same as above */
};


//void add_wc(struct StrongClassifier* sc, struct HaarFeat* feat, int threshold, int pol, int sw[19][19], int epsError, int round);

double alpha_calcul(double epsError);

int wc_calcul(struct WeakClassifier* wc);


void update_weight(double epsError, struct ImgVal* img,int round);

int final_sc(struct StrongClassifier* sc);

void Boost(struct StrongClassifier *sc,struct ImgVal *img, int nbImg, int pos);

void selectBestFeat(struct ImgVal *img,int nbImg);

#endif
