#include<stdlib.h>
#include<stdio.h>

#include"HaarFeatures.h"



int main()
{
	int arr[5][5] = {{10,15,40,52,64},{15,42,1,45,65},{12,26,12,32,5},{24,45,65,95,2},{10,10,20,10,20}};
	struct HaarFeat *vect = malloc(1000*sizeof(struct HaarFeat));
    MakeVectWithFeat(vect,arr);
    struct HaarFeat *test = vect;
    while(test->w!= 100)
    {   
        printf("x : %d, y : %d, w : %d, h: %d, val : %d\n",test->x,test->y,test->w,test->h,test->val);
        test++;
    }           
    free(vect); 
    return 0;

}


void MakeVectWithFeat(struct HaarFeat *vect,int arr[5][5])
{
	vect = FillVectFeatA(vect,arr);
    vect = FillVectFeatB(vect,arr);
    vect = FillVectFeatC(vect,arr);
    vect = FillVectFeatD(vect,arr);
    vect = FillVectFeatE(vect,arr);
    vect->w = 100; 
}

// compute the value of each features of type a
struct Haarfeat* FillVectFeatA(struct HaarFeat *vect, int arr[5][5])
{
    int length = 5;
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
struct Haarfeat* FillVectFeatB(struct HaarFeat *vect, int arr[5][5])
{
    int length = 5;
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
struct Haarfeat* FillVectFeatC(struct HaarFeat *vect, int arr[5][5])
{
    int length = 5;
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
struct Haarfeat* FillVectFeatD(struct HaarFeat *vect, int arr[5][5])
{
    int length = 5;
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
struct Haarfeat* FillVectFeatE(struct HaarFeat *vect, int arr[5][5])
{
    int length = 5;
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
