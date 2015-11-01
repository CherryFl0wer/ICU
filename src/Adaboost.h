#ifndef _ADABOOST_H_
#define _ADABOOST_H_

#include<stdlib.h>
#include<stdio.h>
#include<math.h> 
#include"HaarFeatures.h"

#define T 200 //nbr of round
#define NBIMG 1000


typedef struct WeakClassifier { 
    struct HaarFeat* feature;
    int w;
    int integ[24][24];
    int polarity;
} WeakClassifier;

struct ImgVal {
    struct WeakClassifier wc[1000];// 1000 = number of image to test
    int theta;
    int T;
    int M;
    double e;
};


typedef struct StrongClassifier {
    WeakClassifier wc[200]; /* 200 = number of weakclassifier needed */
    int alpha[200]; /* same as above */
} StrongClassifier;

void Boost(StrongClassifier *sc, int nbImg, int pos);

void add_wc(StrongClassifer* sc, struct HaarFeat* feat, int seuil, int pol, int sw[24][24], int epsError, int round);

double alpha_calcul(int epsError);

int wc_calcul(WeakClassifier* wc);


void update_weight(int epsError, double weight[T][NBIMG], struct ImgVal* img, int posimg, int round);

int final_sc(StrongClassifier* sc);

void Boost(struct StrongClassifier *sc,struct ImgVal *img, int nbImg, int pos);

void selectBestFeat(struct ImgVal *img,int nbImg);

#endif
