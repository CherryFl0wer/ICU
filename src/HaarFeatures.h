# ifndef _HAARFEATURES_H_
# define _HAARFEATURES_H_

#include<stdlib.h>
#include<stdio.h>




struct HaarFeat
{
	int feat,x,y,w,h,val;
};

void ValFeatA(struct HaarFeat *haar,int arr[24][24]);

void ValFeatB(struct HaarFeat *haar,int arr[24][24]);

void ValFeatC(struct HaarFeat *haar,int arr[24][24]);

void ValFeatD(struct HaarFeat *haar,int arr[24][24]);

void ValFeatE(struct HaarFeat *haar,int arr[24][24]);

void MakeVectWithFeat(struct HaarFeat [],int arr[24][24]);

struct HaarFeat* FillVectFeatA(struct HaarFeat *vect,int arr[24][24]);

struct HaarFeat* FillVectFeatB(struct HaarFeat *vect,int arr[24][24]);

struct HaarFeat* FillVectFeatC(struct HaarFeat *vect,int arr[24][24]);

struct HaarFeat* FillVectFeatD(struct HaarFeat *vect,int arr[24][24]);

struct HaarFeat* FillVectFeatE(struct HaarFeat *vect,int arr[24][24]);

#endif
