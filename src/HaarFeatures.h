# ifndef _HAARFEATURES_H_
# define _HAARFEATURES_H_

#include<stdlib.h>
#include<stdio.h>




struct HaarFeat
{
	int feat,x,y,w,h,val;
};


void MakeVectWithFeat(struct HaarFeat [],int arr[24][24]);

struct Haarfeat* FillVectFeatA(struct HaarFeat *vect,int arr[24][24]);

#endif
