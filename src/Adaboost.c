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
    double e = 2;
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
                                    selectBestFeat(img,nbImg);
                                    if(img->e<e)
                                    {
                                        e = img->e;
                                        sc->wc[t] = img->wc[i];
                                    }
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
                                    selectBestFeat(img,nbImg);
                                    if(img->e<e)
                                    {
                                        e = img->e;
                                        sc->wc[t] = img->wc[i];
                                    }
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
                                    selectBestFeat(img,nbImg);
                                    if(img->e<e)
                                    {
                                        e = img->e;
                                        sc->wc[t] = img->wc[i];
                                    } 
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
                                    selectBestFeat(img,nbImg);
                                    if(img->e<e)
                                    {
                                        e = img->e;
                                        sc->wc[t] = img->wc[i];
                                    }
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
                                    selectBestFeat(img,nbImg);
                                    if(img->e<e)
                                    {
                                        e = img->e;
                                        sc->wc[t] = img->wc[i];
                                    }         
                                }
			                }
			            }
		            }
	    	    }

            }

        }


    }  
    free(haar);
}


void selectBestFeat(struct ImgVal *img,int nbImg)
{
//    sorted img + weights
    sort(img);
    double Sp = 0,Sn = 0, Tp = 0, Tn = 0;
    int T = 0;
    int t = img->wc[0].feature->val;
    int M = 0;
    double e = 2;

    for(int i = 0;i<nbImg;i++)
    {
        if(img->wc[i].polarity == 1)
            Tp += img->wc[i].w;
        else
            Tn += img->wc[i].w;
    }
    int jIter = 0;
    int tIter = t;
    int MIter = M;
    int TIter;
    double eIter;
    double Ep,En;
    while(1){
        Ep = Sp+Tn;
        En = Tp+Sn;
        if(Ep<En)
        {
            eIter = Ep;
            TIter = 1;
        }
        else
        {
            eIter = En;
            TIter = -1;
        }
        if(eIter<=e && MIter>M)
        {
            e = eIter;
            t = tIter;
            M = MIter;
            T = TIter;
        }
        if(jIter == nbImg)
            break;
        jIter++;
        while(1){
            if(img->wc[jIter].polarity == -1)
            {
                Sn += img->wc[jIter].w;
                Tn -= img->wc[jIter].w;
            }
            else
            {
                Sp += img->wc[jIter].w;
                Tp -= img->wc[jIter].w;
            }
            if(jIter == nbImg || img->wc[jIter].feature->val)
                break;
            else
                jIter++;
        }
        if(jIter == nbImg)
        {
            tIter = img->wc[jIter].feature->val + 1;
            MIter = 0;
        }
        else
        {
            tIter=(img->wc[jIter].feature->val+img->wc[jIter+1].feature->val)/2;
            MIter = img->wc[jIter+1].feature->val -img->wc[jIter].feature->val;
        }
    }
    img->theta = t;
    img->e=e;
    img->M=M;
    img->T=T;

}
