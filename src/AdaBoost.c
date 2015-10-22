#include<stdlib.h>
#include<stdio.h>


#include"AdaBoost.h"

int main()
{
    return 0;
}
void Boost(struct StrongClassifier *sc, int nbImg, int pos)
{
    int t = 0;
    int T = 200;
    int numImg = 1;

    double weights[T][nbImg];

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
    


}
