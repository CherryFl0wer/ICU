#include<stdlib.h>
#include<stdio.h>


#include"AdaBoost.h"

int main()
{
    return 0;
}

double sumWeight(double weights[],int size)
{
    double res = 0.0;
    for(int i = 0;i<size;i++)
        res += weights[i];
    return res;

}

void Boost(struct StrongClassifier *sc, int nbImg, int pos)
{
    int t = 0;
    int T = 200;
    int numImg = 0;

    double weights[T][nbImg];
    /* initialisation of weights */
    for(int i = 0;i<pos;i++)
    {
        weights[1][i] = 1/(2*pos);
        (sc->wc[i]).polarity = 1;
    }

    for(int i = pos;i<nbImg;i++)
    {
        weights[1][i] = 1/(2*(nbImg-pos));
        (sc->wc[i]).polarity = 0;                
    }



    /* main loop */
    for(;t<T;t++)
    {
        for(int i = 0;i<nbImg;i++)
        {
            weights[t][i] /= sumWeight(weights[t],nbImg);
        }



        /* select the vest weak classifier */



    }  

}
