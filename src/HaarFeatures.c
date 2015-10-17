#include<stdlib.h>
#include<stdio.h>

#include"HaarFeatures.h"



int main(int argc, char *argv[])
{
	int arr[5][5] = {{10,15,40,52,64},{15,42,1,45,65},{12,26,12,32,5},{24,45,65,95,2},{10,10,20,10,20}};
	return 0;
}


void MakeVectWithFeat(struct HaarFeat vect[],int arr[24][24])
{
	
}
// compute the value of each features of type a
struct Haarfeat* FillVectFeatA(struct HaarFeat *vect, int arr[24][24])
{
    int length = 24;
    struct HaarFeat *haar = malloc(sizeof(struct HaarFeat));
    haar->feat = 1;

    haar->x = 0;
    haar->y = 0;
    haar->w = 0;
    haar->h = 0;
	for(; haar->x<length;haar->x++)
	{
		for(;haar->y<length;haar->y++)
		{
			for(;haar->x+haar->h<length;haar->h++)
			{
				for(;haar->y+2*(haar->w)<length;haar->w++)
				{
                    //compute haar->val
                    int white = arr[haar->x][haar->y]
                        +arr[haar->x+haar->h][haar->y+haar->w]
                        -arr[haar->x][haar->y+haar->w]
                        -arr[haar->x+haar->h][haar->y];
                    int black = arr[haar->x][haar->y+haar->w]
                        +arr[haar->x+haar->h][haar->y+2*(haar->w)]
                        -arr[haar->x][haar->y+2*(haar->w)]
                        -arr[haar->x+haar->h][haar->y+haar->w];
                    vect->val = black - white;
                    *vect = *haar;
                    vect++;
				}
			}
		}
	}

    free(haar);
    return vect;
}	
