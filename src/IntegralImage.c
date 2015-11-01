#include "IntegralImage.h"
#include "SDLPixel.h"

void integralImg(int **arr, int x, int y) { 

	for(int i = 1; i < x; i++)
		arr[i][0] += arr[i-1][0]; 
	
	for(int j = 1; j < y; j++)
		arr[0][j] += arr[0][j-1];

	for(int j = 1; j < y; j++)
		for(int i = 1; i < x; i++)
			arr[i][j] +=  arr[i-1][j] + arr[i][j-1] - arr[i-1][j-1]; 	

}


void imgToGreyScale(SDL_Surface* img) {
	uint8_t r, g, b;
	uint32_t pixel = 0;
	float luminance = 0.0;
	for(int i = 0; i < img->w; i++) {
		for(int j = 0; j < img->h; j++) {
			SDL_GetRGB(getpixel(img,i,j), img->format, &r, &g, &b);
			luminance = 0.299 * r + 0.587 * g + 0.114 * b;
			r = g = b = luminance / 3;
		  pixel = SDL_MapRGB(img->format, r, g, b);
		  putpixel(img, i, j, pixel);
		}
	}
}
