#include<stdlib.h>
#include<stdio.h>


#include"Adaboost.h"
#include"HaarFeatures.h"
#include"Sort.h"

int main()
{
    return 0;
}

double sumWeight(struct WeakClassifier *wc,int size)
{
    double res = 0.0;
    for(int i = 0;i<size;i++)
        res += wc[i].w;
    return res;

}

void Boost(struct StrongClassifier *sc,struct ImgVal *img, int nbImg, int pos)
{
    int t = 0;
    int T = 200;
    int numImg = 0;
    struct HaarFeat* haar = malloc(sizeof(struct HaarFeat));
    /* initialisation of weights */
    for(int i = 0;i<pos;i++)
    {
        img->wc[i].w = 1/(2*pos);
        (img->wc[i]).polarity = 1;
    }

    for(int i = pos;i<nbImg;i++)
    {
        img->wc[i].w = 1/(2*(nbImg-pos));
        (img->wc[i]).polarity = -1;                
    }



    /* main loop */
    for(;t<T;t++)
    {
        for(int i = 0;i<nbImg;i++)
        {
            img->wc[i].w /= sumWeight(img->wc,nbImg);
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
        		for(haar->x = 0; haar->x<24; haar->x++)
	        	{
		            for(haar->y = 0; haar->y<24; haar->y++)
		            {
			            for(haar->h = 1; haar->x+haar->h<24; haar->h++)
			            {
			                for(haar->w = 1;haar->y+2*haar->w<24; haar->w++)
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
        		for(haar->x = 0; haar->x<24; haar->x++)
	        	{
		            for(haar->y = 0; haar->y<24; haar->y++)
		            {
			            for(haar->h = 1; haar->x+haar->h<24; haar->h++)
			            {
			                for(haar->w = 1;haar->y+3*haar->w<24; haar->w++)
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
        		for(haar->x = 0; haar->x<24; haar->x++)
	        	{
		            for(haar->y = 0; haar->y<24; haar->y++)
		            {
			            for(haar->h = 1; haar->x+2*haar->h<24; haar->h++)
			            {
			                for(haar->w = 1; haar->y+haar->w<24; haar->w++)
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
        		for(haar->x = 0; haar->x<24; haar->x++)
	        	{
		            for(haar->y = 0; haar->y<24; haar->y++)
		            {
			            for(haar->h = 1; haar->x+3*haar->h<24; haar->h++)
			            {
			                for(haar->w = 1; haar->y+haar->w<24; haar->w++)
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
        		for(haar->x = 0; haar->x<24; haar->x++)
	        	{
		            for(haar->y = 0; haar->y<24; haar->y++)
		            {
			            for(haar->h = 1; haar->x+2*haar->h<24; haar->h++)
			            {
			                for(haar->w = 1;haar->y+2*haar->w<24; haar->w++)
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


//void selectBestFeat(struct ImgVal *img,double *weights,int nbImg)
//{
//    sorted img + weights
//    quick_sort    
//}
