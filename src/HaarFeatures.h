# ifndef _HAARFEATURES_H_
# define _HAARFEATURES_H_

#include<stdlib.h>
#include<stdio.h>




struct HaarFeat
{
	int feat,x,y,w,h,val;
};


void MakeVectWithFeat(struct HaarFeat [],int arr[5][5]);

struct Haarfeat* FillVectFeatA(struct HaarFeat *vect,int arr[5][5]);

struct Haarfeat* FillVectFeatB(struct HaarFeat *vect,int arr[5][5]);

struct Haarfeat* FillVectFeatC(struct HaarFeat *vect,int arr[5][5]);

struct Haarfeat* FillVectFeatD(struct HaarFeat *vect,int arr[5][5]);

struct Haarfeat* FillVectFeatE(struct HaarFeat *vect,int arr[5][5]);

#endif
