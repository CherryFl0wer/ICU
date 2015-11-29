#include<stdlib.h>
#include<stdio.h>

#include"HaarFeatures.h"


void ValFeatA(struct HaarFeat *haar,int arr[19][19])
{
    int x = haar->x;
    int y = haar->y;
    int w = haar->w;
    int h = haar->h;
    
    int a = arr[x][y];
    int b = arr[x][y+w];
    int c = arr[x+h][y];
    int d = arr[x+h][y+w];
    int e = arr[x][y+2*w];
    int f = arr[x+h][y+2*w];
    
    haar->val = -a -2*d + 2*b + c - e + f;
   
}

void ValFeatB(struct HaarFeat *haar,int arr[19][19])
{ 
    int x = haar->x;
    int y = haar->y;
    int w = haar->w;
    int h = haar->h;
    
    int a = arr[x][y];
    int b = arr[x][y+w];
    int c = arr[x+h][y];
    int d = arr[x+h][y+w];
    int e = arr[x][y+2*w];
    int f = arr[x+h][y+2*w];
    int g = arr[x][y+3*w];
    int i = arr[x+h][y+3*w];

                  
    haar->val = -a -2*d + 2*b + c -2*e + 2*f - i + g;
                

}

void ValFeatC(struct HaarFeat *haar,int arr[19][19])
{ 
    int x = haar->x;
    int y = haar->y;
    int w = haar->w;
    int h = haar->h;
    
    int a = arr[x][y];
    int b = arr[x][y+w];
    int c = arr[x+h][y];
    int d = arr[x+h][y+w];
    int e = arr[x+2*h][y];
    int f = arr[x+2*h][y+w];

    haar->val = -a -2*d + b +2*c - e + f;
}


void ValFeatD(struct HaarFeat *haar,int arr[19][19])
{ 
    int x = haar->x;
    int y = haar->y;
    int w = haar->w;
    int h = haar->h;
    
    int a = arr[x][y];
    int b = arr[x][y+w];
    int c = arr[x+h][y];
    int d = arr[x+h][y+w];
    int e = arr[x+2*h][y];
    int f = arr[x+2*h][y+w];
    int g = arr[x+3*h][y];
    int i = arr[x+3*h][y+w];

    haar->val = -a -2*d + b + 2*c -2*e + 2*f - i + g;
            
}


void ValFeatE(struct HaarFeat *haar,int arr[19][19])
{ 
    int x = haar->x;
    int y = haar->y;
    int w = haar->w;
    int h = haar->h;
                    
    int a = arr[x][y];
    int b = arr[x][y+w];
    int c = arr[x+h][y];
    int d = arr[x+h][y+w];
    int e = arr[x][y+2*w];
    int f = arr[x+h][y+2*w];
    int g = arr[x+2*h][y];
    int i = arr[x+2*h][y+w];
    int j = arr[x+2*h][y+2*w];

    haar->val = -a -4*d + 2*b + 2*c -e + 2*f +2*i - g - j;
}

//fonction for detection
void ValFeatA_det(struct HaarFeat *haar,int **arr)
{
    int x = haar->x;
    int y = haar->y;
    int w = haar->w;
    int h = haar->h;
    
    int a = arr[x][y];
    int b = arr[x][y+w];
    int c = arr[x+h][y];
    int d = arr[x+h][y+w];
    int e = arr[x][y+2*w];
    int f = arr[x+h][y+2*w];
    
    haar->val = -a -2*d + 2*b + c - e + f;
   
}

void ValFeatB_det(struct HaarFeat *haar,int **arr)
{ 
    int x = haar->x;
    int y = haar->y;
    int w = haar->w;
    int h = haar->h;
    
    int a = arr[x][y];
    int b = arr[x][y+w];
    int c = arr[x+h][y];
    int d = arr[x+h][y+w];
    int e = arr[x][y+2*w];
    int f = arr[x+h][y+2*w];
    int g = arr[x][y+3*w];
    int i = arr[x+h][y+3*w];

                  
    haar->val = -a -2*d + 2*b + c -2*e + 2*f - i + g;
                

}

void ValFeatC_det(struct HaarFeat *haar,int **arr)
{ 
    int x = haar->x;
    int y = haar->y;
    int w = haar->w;
    int h = haar->h;
    
    int a = arr[x][y];
    int b = arr[x][y+w];
    int c = arr[x+h][y];
    int d = arr[x+h][y+w];
    int e = arr[x+2*h][y];
    int f = arr[x+2*h][y+w];

    haar->val = -a -2*d + b +2*c - e + f;
}


void ValFeatD_det(struct HaarFeat *haar,int **arr)
{ 
    int x = haar->x;
    int y = haar->y;
    int w = haar->w;
    int h = haar->h;
    
    int a = arr[x][y];
    int b = arr[x][y+w];
    int c = arr[x+h][y];
    int d = arr[x+h][y+w];
    int e = arr[x+2*h][y];
    int f = arr[x+2*h][y+w];
    int g = arr[x+3*h][y];
    int i = arr[x+3*h][y+w];

    haar->val = -a -2*d + b + 2*c -2*e + 2*f - i + g;
            
}


void ValFeatE_det(struct HaarFeat *haar,int **arr)
{ 
    int x = haar->x;
    int y = haar->y;
    int w = haar->w;
    int h = haar->h;
                    
    int a = arr[x][y];
    int b = arr[x][y+w];
    int c = arr[x+h][y];
    int d = arr[x+h][y+w];
    int e = arr[x][y+2*w];
    int f = arr[x+h][y+2*w];
    int g = arr[x+2*h][y];
    int i = arr[x+2*h][y+w];
    int j = arr[x+2*h][y+2*w];

    haar->val = -a -4*d + 2*b + 2*c -e + 2*f +2*i - g - j;
}


// Fill vect with all different features with different sizes
void MakeVectWithFeat(struct HaarFeat *vect,int arr[19][19])
{
	vect = FillVectFeatA(vect,arr);
    vect = FillVectFeatB(vect,arr);
    vect = FillVectFeatC(vect,arr);
    vect = FillVectFeatD(vect,arr);
    vect = FillVectFeatE(vect,arr);
    vect->val = -1 ; 
}

// compute the value of each features of type a
struct HaarFeat* FillVectFeatA(struct HaarFeat *vect, int arr[19][19])
{
    int length = 19;
    struct HaarFeat *haar = malloc(sizeof(struct HaarFeat));
    haar->feat = 1;

    
	for(int x = 0; x<length; x++)
	{
		for(int y = 0; y<length; y++)
		{
			for(int h = 1; x+h<length; h++)
			{
				for(int w = 1; y+2*w<length; w++)
				{
                    //compute haar->val

                    haar->x = x;
                    haar->y = y;
                    haar->w = w;
                    haar->h = h;
                    
                    ValFeatA(haar,arr); 
                    
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
struct HaarFeat* FillVectFeatB(struct HaarFeat *vect, int arr[19][19])
{
    int length = 19;
    struct HaarFeat *haar = malloc(sizeof(struct HaarFeat));
    haar->feat = 2;

    
	for(int x = 0; x<length; x++)
	{
		for(int y = 0; y<length; y++)
		{
			for(int h = 1; x+h<length; h++)
			{
				for(int w = 1; y+3*w<length; w++)
				{
                    //compute haar->val
                    haar->x = x;
                    haar->y = y;
                    haar->w = w;
                    haar->h = h;
                    
                    ValFeatB(haar,arr); 
                    
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
struct HaarFeat* FillVectFeatC(struct HaarFeat *vect, int arr[19][19])
{
    int length = 19;
    struct HaarFeat *haar = malloc(sizeof(struct HaarFeat));
    haar->feat = 3;

    
	for(int x = 0; x<length; x++)
	{
		for(int y = 0; y<length; y++)
		{
			for(int h = 1; x+2*h<length; h++)
			{
				for(int w = 1; y+w<length; w++)
				{
                    //compute haar->val
                    haar->x = x;
                    haar->y = y;
                    haar->w = w;
                    haar->h = h;
                    
                    ValFeatC(haar,arr); 
                    
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
struct HaarFeat* FillVectFeatD(struct HaarFeat *vect, int arr[19][19])
{
    int length = 19;
    struct HaarFeat *haar = malloc(sizeof(struct HaarFeat));
    haar->feat = 4;

    
	for(int x = 0; x<length; x++)
	{
		for(int y = 0; y<length; y++)
		{
			for(int h = 1; x+3*h<length; h++)
			{
				for(int w = 1; y+w<length; w++)
				{
                    //compute haar->val
                    haar->x = x;
                    haar->y = y;
                    haar->w = w;
                    haar->h = h;
                   
                    ValFeatD(haar,arr); 

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
struct HaarFeat* FillVectFeatE(struct HaarFeat *vect, int arr[19][19])
{
    int length = 19;
    struct HaarFeat *haar = malloc(sizeof(struct HaarFeat));
    haar->feat = 5;

    
	for(int x = 0; x<length; x++)
	{
		for(int y = 0; y<length; y++)
		{
			for(int h = 1; x+2*h<length; h++)
			{
				for(int w = 1; y+2*w<length; w++)
				{
                    //compute haar->val
                    haar->x = x;
                    haar->y = y;
                    haar->w = w;
                    haar->h = h;
               
                    ValFeatE(haar,arr); 
                    
                    *vect = *haar;
                    vect++;
				}
			}
		}
	}

    free(haar);
    return vect;
}
