#include<stdlib.h>
#include<stdio.h>

#include"HaarFeatures.h"


// Fill vect with all different features with different sizes
void MakeVectWithFeat(struct HaarFeat *vect,int arr[24][24])
{
	vect = FillVectFeatA(vect,arr);
    vect = FillVectFeatB(vect,arr);
    vect = FillVectFeatC(vect,arr);
    vect = FillVectFeatD(vect,arr);
    vect = FillVectFeatE(vect,arr);
    vect->val = -1 ; 
}

// compute the value of each features of type a
struct HaarFeat* FillVectFeatA(struct HaarFeat *vect, int arr[24][24])
{
    int length = 24;
    struct HaarFeat *haar = malloc(sizeof(struct HaarFeat));
    haar->feat = 1;

    
    int a = 0,b = 0, c = 0, d = 0, e = 0, f = 0;
	for(int x = 0; x<length; x++)
	{
		for(int y = 0; y<length; y++)
		{
			for(int h = 1; x+h<length; h++)
			{
				for(int w = 1; y+2*w<length; w++)
				{
                    //compute haar->val
                    a = arr[x][y];
                    b = arr[x][y+w];
                    c = arr[x+h][y];
                    d = arr[x+h][y+w];
                    e = arr[x][y+2*w];
                    f = arr[x+h][y+2*w];

                    haar->x = x;
                    haar->y = y;
                    haar->w = w;
                    haar->h = h;
                    haar->val = -a -2*d + 2*b + c - e + f;
                
                    
                    *vect = *haar;
                    vect++;
				}
			}
		}
	}

    free(haar);
    return vect;
}


//Compute FeatB in vect
struct HaarFeat* FillVectFeatB(struct HaarFeat *vect, int arr[24][24])
{
    int length = 24;
    struct HaarFeat *haar = malloc(sizeof(struct HaarFeat));
    haar->feat = 2;

    
    int a = 0,b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, i = 0;
	for(int x = 0; x<length; x++)
	{
		for(int y = 0; y<length; y++)
		{
			for(int h = 1; x+h<length; h++)
			{
				for(int w = 1; y+3*w<length; w++)
				{
                    //compute haar->val
                    a = arr[x][y];
                    b = arr[x][y+w];
                    c = arr[x+h][y];
                    d = arr[x+h][y+w];
                    e = arr[x][y+2*w];
                    f = arr[x+h][y+2*w];
                    g = arr[x][y+3*w];
                    i = arr[x+h][y+3*w];

                    haar->x = x;
                    haar->y = y;
                    haar->w = w;
                    haar->h = h;
                    haar->val = -a -2*d + 2*b + c -2*e + 2*f - i + g;
                
                    
                    *vect = *haar;
                    vect++;
				}
			}
		}
	}

    free(haar);
    return vect;
}

//Compute FeatC in vect
struct HaarFeat* FillVectFeatC(struct HaarFeat *vect, int arr[24][24])
{
    int length = 24;
    struct HaarFeat *haar = malloc(sizeof(struct HaarFeat));
    haar->feat = 3;

    
    int a = 0,b = 0, c = 0, d = 0, e = 0, f = 0;
	for(int x = 0; x<length; x++)
	{
		for(int y = 0; y<length; y++)
		{
			for(int h = 1; x+2*h<length; h++)
			{
				for(int w = 1; y+w<length; w++)
				{
                    //compute haar->val
                    a = arr[x][y];
                    b = arr[x][y+w];
                    c = arr[x+h][y];
                    d = arr[x+h][y+w];
                    e = arr[x+2*h][y];
                    f = arr[x+2*h][y+w];

                    haar->x = x;
                    haar->y = y;
                    haar->w = w;
                    haar->h = h;
                    haar->val = -a -2*d + b +2*c - e + f;
                
                    
                    *vect = *haar;
                    vect++;
				}
			}
		}
	}

    free(haar);
    return vect;
}

//Compute FeatD in vect
struct HaarFeat* FillVectFeatD(struct HaarFeat *vect, int arr[24][24])
{
    int length = 24;
    struct HaarFeat *haar = malloc(sizeof(struct HaarFeat));
    haar->feat = 4;

    
    int a = 0,b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, i = 0;
	for(int x = 0; x<length; x++)
	{
		for(int y = 0; y<length; y++)
		{
			for(int h = 1; x+3*h<length; h++)
			{
				for(int w = 1; y+w<length; w++)
				{
                    //compute haar->val
                    a = arr[x][y];
                    b = arr[x][y+w];
                    c = arr[x+h][y];
                    d = arr[x+h][y+w];
                    e = arr[x+2*h][y];
                    f = arr[x+2*h][y+w];
                    g = arr[x+3*h][y];
                    i = arr[x+3*h][y+w];

                    haar->x = x;
                    haar->y = y;
                    haar->w = w;
                    haar->h = h;
                    haar->val = -a -2*d + b + 2*c -2*e + 2*f - i + g;
                
                    
                    *vect = *haar;
                    vect++;
				}
			}
		}
	}

    free(haar);
    return vect;
}


//Compute FeatE in vect
struct HaarFeat* FillVectFeatE(struct HaarFeat *vect, int arr[24][24])
{
    int length = 24;
    struct HaarFeat *haar = malloc(sizeof(struct HaarFeat));
    haar->feat = 5;

    
    int a = 0,b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, i = 0, j = 0;
	for(int x = 0; x<length; x++)
	{
		for(int y = 0; y<length; y++)
		{
			for(int h = 1; x+2*h<length; h++)
			{
				for(int w = 1; y+2*w<length; w++)
				{
                    //compute haar->val
                    a = arr[x][y];
                    b = arr[x][y+w];
                    c = arr[x+h][y];
                    d = arr[x+h][y+w];
                    e = arr[x][y+2*w];
                    f = arr[x+h][y+2*w];
                    g = arr[x+2*h][y];
                    i = arr[x+2*h][y+w];
                    j = arr[x+2*h][y+2*w];

                    haar->x = x;
                    haar->y = y;
                    haar->w = w;
                    haar->h = h;
                    haar->val = -a -4*d + 2*b + 2*c -e + 2*f +2*i - g - j;
                
                    
                    *vect = *haar;
                    vect++;
				}
			}
		}
	}

    free(haar);
    return vect;
}
