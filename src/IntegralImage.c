#include "IntegralImage.h"
#include "SDLPixel.h"

void integralImg(uint8_t **arr, int x, int y) { 

	for(int i = 1; i < x; i++)
		arr[i][0] += arr[i-1][0]; 
	
	for(int j = 1; j < y; j++)
		arr[0][j] += arr[0][j-1];

	for(int j = 1; j < y; j++)
		for(int i = 1; i < x; i++)
			arr[i][j] +=  arr[i-1][j] + arr[i][j-1] - arr[i-1][j-1]; 	

}


void imgToGreyScale(SDL_Surface* img, uint32_t** imgArr, uint8_t **bwImgTab) {
	uint8_t r, g, b;

	float luminance = 0.0;
	for(int i = 0; i < img->w; i++) {
		for(int j = 0; j < img->h; j++) {
			SDL_GetRGB(imgArr[i][j], img->format, &r, &g, &b);
			luminance = 0.299 * r + 0.587 * g + 0.114 * b;
			r = g = b = luminance / 3;
			bwImgTab[i][j] = r; // or g or b whatever
		//	pixel = SDL_MapRGB(img->format, r, g, b);
		//	putpixel(img, i, j, pixel);
		}
	}
}
