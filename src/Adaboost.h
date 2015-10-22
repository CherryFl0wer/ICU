#ifndef ADABOOST_HEADER
#define ADABOOST_HEADER
#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>

typedef struct t_weak_classifier {
	int polarity;  // Polarité de la feature
	int threshold; // seuil 
	uint32_t subwindow[24][24];
	HaarFeat* feature;
} WeakClassifier;

int h(WeakClassifier *weak);

void polarityImage(char* posdir, char* negdir);
#endif
