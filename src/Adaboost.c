#include "Adaboost.h"

int h(WeakClassifier *weak) {
	return ((weak->feature->val * weak->polarity) < (weak->polarity * weak->threshold)) ? 1 : 0;
}

void polarityImage(char* posdir, char* negdir) {
	// En attentante de la db pour test
}


