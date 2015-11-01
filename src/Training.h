#ifndef _TRAINING_HEADER
#define _TRAINING_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "./Utils.h"
#include "./Adaboost.h"
#include "./HaarFeature.h"

const char* kTrainingFileName = "./training.bin";

void save_training(struct StrongClassifier* sc, int round); 
void get_training(struct StrongClassifier* sc);
int create_sc_with_string(struct StrongClassifier* sc, char* str, int round);
#endif
