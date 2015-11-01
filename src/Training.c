#include "Training.h"

void save_training(struct StrongClassifier* sc, int round) {
  FILE *trainingFile = NULL;
  trainingFile = fopen("./training.bin", "a+"); 
  if (!trainingFile) {
    //perror("Failed opening file %s", kTrainingFileName);
    exit(1);
  }
 
  for(int i = 0; i < round; i++) {
     fprintf(trainingFile, 
        "Fx:%d,Fy:%d,Fw:%d,Fh:%d,Ft:%d,Th:%d,Po:%d,Al:%d\n",
        sc->wc[i].feature->x,
        sc->wc[i].feature->y,
        sc->wc[i].feature->w,
        sc->wc[i].feature->h,
        sc->wc[i].feature->feat,
        sc->wc[i].threshold,
        sc->wc[i].polarity,
        sc->alpha[i]);
  }
  fclose(trainingFile);
}


void get_training(struct StrongClassifier* sc) {
  FILE *trainingFile = NULL;
  trainingFile = fopen("./training.bin", "r");
  if(!trainingFile) {
   exit(1);
  }
 
 // char line[256];
  int i = 0;
  char *line = NULL;
  size_t len;
  while(getlines(&line, &len, trainingFile)!=-1) {
   if(!create_sc_with_string(sc, line, i)) break;
   i++;
  }

  fclose(trainingFile);
}

int create_sc_with_string(struct StrongClassifier* sc, char* str, int round) {
  if(str != NULL) { 
   const char delimiter[2] = ","; 
   char* token;
   int i = 0;
   int scValues[8] = { 0 };
   token = strtok(str, delimiter);
  
   while(token != NULL) {
    char tokenval[20]; 
    memset(tokenval, '\0', sizeof(tokenval));
    strcpy(tokenval, token+3);

    scValues[i] = atoi(tokenval);
    
    token = strtok(NULL, delimiter);
    i++;
   } 
    
   struct WeakClassifier weak;
   weak.feature = malloc(sizeof(struct HaarFeat));
   weak.feature->x = scValues[0];
   weak.feature->y = scValues[1];
   weak.feature->w = scValues[2];
   weak.feature->h = scValues[3];
   weak.feature->feat = scValues[4];
   weak.feature->val = 0;

   weak.w = 0;
   weak.threshold = scValues[5];
   weak.polarity  = scValues[6];
   for(int i = 0; i < 19; i++)
     for(int j = 0; j < 19; j++)
       weak.integ[i][j] = 0;
    
   sc->wc[round] = weak;
   sc->alpha[round] = scValues[7];
    
   return 1;
  }

  return 0;
}

/*int main(int argc, char* argv[]) {
  struct StrongClassifier *sc = malloc(sizeof(struct StrongClassifier));
  for(int i = 0; i < 5; i++) {
    struct WeakClassifier weak;
    weak.feature = malloc(sizeof(struct HaarFeat));
    weak.feature->x = 1;
    weak.feature->y = 2;
    weak.feature->w = 3;
    weak.feature->h = 5;
    weak.feature->val = 0;
    weak.feature->feat = 0;

    weak.w = 0;
    weak.threshold = i;
    for(int j = 0; j<19; j++)
      for(int l = 0; l < 19; l++)
        weak.integ[j][l] = 0;

    weak.polarity = i % 5;
    sc->wc[i] = weak;
    sc->alpha[i] = i % 3;
  }
  
  save_training(sc, 5);
  
  free(sc);

  struct StrongClassifier *nsc = malloc(sizeof(struct StrongClassifier));
  
  get_training(nsc);
  
  for(int i = 0; i <  5; i++) {
    printf("Round %d: Fx :%d / Fy :%d / Fw :%d / Fh :%d / Feature :%d / Threshold : %d / Polarity : %d / Alpha :%d \n", i, 
        nsc->wc[i].feature->x, 
        nsc->wc[i].feature->y,
        nsc->wc[i].feature->w,
        nsc->wc[i].feature->h,
        nsc->wc[i].feature->feat,
        nsc->wc[i].threshold,
        nsc->wc[i].polarity,
        nsc->alpha[i]);
  } 
  for(int i = 0; i < 5; i++) 
    free(nsc->wc[i].feature);
  free(nsc);

  return 0;
} */
