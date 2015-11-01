#ifndef _ADABOOST_H_
#define _ADABOOST_H_

#include<stdlib.h>
#include<stdio.h>
#include<math.h> 
#include"HaarFeatures.h"

#define NBIMG 1000

const int T = 190; //nbr of round

struct WeakClassifier { 
    struct HaarFeat* feature;
    int w,threshold;
    int integ[24][24];
    int polarity;
};

struct ImgVal {
    struct WeakClassifier wc[1000];// 1000 = number of image to test
    int theta;
    int T;
    int M;
    double e;
};


struct StrongClassifier {
    struct WeakClassifier wc[190]; /* 190 = number of weakclassifier needed */
    int alpha[190]; /* same as above */
};


void add_wc(struct StrongClassifier* sc, struct HaarFeat* feat, int threshold, int pol, int sw[24][24], int epsError, int round);

double alpha_calcul(int epsError);

int wc_calcul(struct WeakClassifier* wc);


void update_weight(int epsError, struct ImgVal* img,int round);

int final_sc(struct StrongClassifier* sc);

void Boost(struct StrongClassifier *sc,struct ImgVal *img, int nbImg, int pos);

void selectBestFeat(struct ImgVal *img,int nbImg);

#endif
