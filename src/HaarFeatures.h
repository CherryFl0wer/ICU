# ifndef _HAARFEATURES_H_
# define _HAARFEATURES_H_

#include<stdlib.h>
#include<stdio.h>




struct HaarFeat
{
	int feat,x,y,w,h,val;
};

void ValFeatA(struct HaarFeat *haar,int arr[19][19]);

void ValFeatB(struct HaarFeat *haar,int arr[19][19]);

void ValFeatC(struct HaarFeat *haar,int arr[19][19]);

void ValFeatD(struct HaarFeat *haar,int arr[19][19]);

void ValFeatE(struct HaarFeat *haar,int arr[19][19]);

void ValFeatA_det(struct HaarFeat *haar,int **arr);

void ValFeatB_det(struct HaarFeat *haar,int **arr);

void ValFeatC_det(struct HaarFeat *haar,int **arr);

void ValFeatD_det(struct HaarFeat *haar,int **arr);

void ValFeatE_det(struct HaarFeat *haar,int **arr);


void MakeVectWithFeat(struct HaarFeat [],int arr[19][19]);

struct HaarFeat* FillVectFeatA(struct HaarFeat *vect,int arr[19][19]);

struct HaarFeat* FillVectFeatB(struct HaarFeat *vect,int arr[19][19]);

struct HaarFeat* FillVectFeatC(struct HaarFeat *vect,int arr[19][19]);

struct HaarFeat* FillVectFeatD(struct HaarFeat *vect,int arr[19][19]);

struct HaarFeat* FillVectFeatE(struct HaarFeat *vect,int arr[19][19]);

#endif
