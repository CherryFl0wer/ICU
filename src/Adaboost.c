#include"AdaBoost.h"

int main()
{
		StrongClassifer* sc = malloc(sizeof(StrongClassifier));
		Boost(sc, NULL, 200, 50);
		free(sc);

    return 0;
}

double sumWeight(double weights[],int size)
{
    double res = 0.0;
    for(int i = 0;i<size;i++)
        res += weights[i];
    return res;

}

void Boost(struct StrongClassifier *sc,struct ImgVal *img, int nbImg, int pos)
{
    int t = 0;
    int numImg = 0;
    struct HaarFeat* Haar = malloc(sizeof(struct HaarFeat));
    double weights[T][nbImg];
    /* initialisation of weights */
    for(int i = 0;i<pos;i++)
    {
        weights[1][i] = 1/(2*pos);
        (img->wc[i]).polarity = 1;
    }

    for(int i = pos;i<nbImg;i++)
    {
        weights[1][i] = 1/(2*(nbImg-pos));
        (img->wc[i]).polarity = -1;                
    }



    /* main loop */
    for(;t<T;t++)
    {
        for(int i = 0;i<nbImg;i++)
        {
            weights[t][i] /= sumWeight(weights[t],nbImg);
        }

        /* select the best weak classifier */
        for(int feat = 1;feat<=5;feat++)
        {
            haar->x = 0;
            haar->y = 0;
            haar->w = 0;
            haar->h = 0;
            if(feat ==1)
            {
              haar->feat = 1;
        			for(int haar->x = 0; haar->x<24; haar->x++)
	        		{
		            for(int haar->y = 0; haar->y<24; haar->y++)
		            {
			            for(int haar->h = 1; haar->x+haar->h<24; haar->h++)
			            {
			              for(int haar->w = 1;haar->y+2*haar->w<24; haar->w++)
			              {
                    	for(int i = 0;i<nbImg;i++)
                      {
                    		ValFeatA(haar,img->wc[i].integ); 
                        img->wc[i].feature = haar;
                      }
                    }
			            }
		            }
	    	    	}  
            }
            else if(feat == 2)
            {
           	  haar->feat = 2;
        		  for(int haar->x = 0; haar->x<24; haar->x++)
	        		{
		            for(int haar->y = 0; haar->y<24; haar->y++)
		            {
			            for(int haar->h = 1; haar->x+haar->h<24; haar->h++)
			            {
			               for(int haar->w = 1;haar->y+3*haar->w<24; haar->w++)
			               {
                    		for(int i = 0;i<nbImg;i++)
                        {
                    			ValFeatB(haar,img->wc[i].integ); 
                          img->wc[i].feature = haar;
                        }
                     }
			            }
		            }
	    	    	}
            }
            else if(feat == 3)
            {
            	haar->feat = 3;
        			for(int haar->x = 0; haar->x<24; haar->x++)
	        		{
		            for(int haar->y = 0; haar->y<24; haar->y++)
		            {
			            for(int haar->h = 1; haar->x+2*haar->h<24; haar->h++)
			            {
			                for(int haar->w = 1; haar->y+haar->w<24; haar->w++)
			                {                    
                    		for(int i = 0;i<nbImg;i++)
                        {
                    			ValFeatC(haar,img->wc[i].integ); 
                          img->wc[i].feature = haar;
                        }
                      }
			            }	
		            }
	    	    	}

            }
            else if(feat == 4)
            {
            	haar->feat = 4;
        			for(int haar->x = 0; haar->x<24; haar->x++)
	        		{
		            for(int haar->y = 0; haar->y<24; haar->y++)
		            {
			            for(int haar->h = 1; haar->x+3*haar->h<24; haar->h++)
			            {
			                for(int haar->w = 1; haar->y+haar->w<24; haar->w++)
			                {
                      	for(int i = 0;i<nbImg;i++)
                        {
                    		  ValFeatD(haar,img->wc[i].integ); 
                          img->wc[i].feature = haar;
                        }
			                }
			            }
		            }
	    	    	}

            }
            else if(feat == 5)
            {
              haar->feat = 5;
        			for(int haar->x = 0; haar->x<24; haar->x++)
	        		{
		            for(int haar->y = 0; haar->y<24; haar->y++)
		            {
			            for(int haar->h = 1; haar->x+2*haar->h<24; haar->h++)
			            {
			              for(int haar->w = 1;haar->y+2*haar->w<24; haar->w++)
			              {
                      for(int i = 0;i<nbImg;i++)
                      {
                    		ValFeatE(haar,img->wc[i].integ); 
                        img->wc[i].feature = haar;
                      }
			              }
			            }
		            }
	    	   		}

            }

        }


    }  

}


double alpha_calcul(int epsError) {
	return log((1-epsError)/epsError);
}


// Don't know if it's better to replace by WeakClassifier wc
void add_wc(StrongClassifier* sc, struct HaarFeat* feat, int threshold, int pol, int sw[24][24], int epsError, int round) {
	WeakClassifier weak;
	weak.feature 		= feat;
	weak.threshold  = threshold;
	weak.polarity 	= pol;
	weak.integ 			= sw;
	
	sc->wc[round] 	= weak;
	
	// calcul alpha
	sc->alpha[round] = alpha_calcul(epsError);
}

int wc_calcul(WeakClassifier* wc) {
	return (wc->feature->val * wc->polarity < wc->threshold * wc->polarity) ? 1 : 0;  
}

void update_weight(int epsError, double weight[T][NBIMG], struct ImgVal* img, int posimg, int round) {
	if(round < T) {
		double beta = epsError / (1 - espError);
		int ei = 0;
		for(int i = 1; i < NBIMG; i++) { 
			if(wc_calcul(img->wc[i]) * img->wc[i].polarity * -alpha_calcul(epsError) > 0)
				ei = 1;
			else
				ei = 0;
			
			weight[round+1][i] = weight[round][i] * pow(beta, 1-ei);
		} 
		
	}
}


// C(X) where X is an image. 
// TODO : final_sc(SDL_Surface* img, StrongClassifier* sc) ??
int	final_sc(StrongClassifier* sc) {
	double sumSC = 0, sumAlpha = 0;
	for(int i = 0; i < T; i++) {
		sumSC += sc->alpha[i] * wc_calcul(sc->wc[round]);
		sumAlpha += sc->alpha[i] * 0.5;
	}

	return (sumSC >= sumAlpha) ? 1 : 0;
}
