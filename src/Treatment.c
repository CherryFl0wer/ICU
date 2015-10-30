#include "Treatment.h"
#include "SDLPixel.h"


// increase the contrast of a picture
void normalize(SDL_Surface *img)
{
    Uint8 max = 0,min = 255;
    Uint8 r = 0;
    Uint32 pix = 0;
    //determined max and min
    for(int i = 0; i < img->w ; i++)
    {
        for(int j = 0; j < img->h; j++)
        {
            pix = getpixel(img,i,j);
            SDL_GetRGB(pix,img->format,&r,&r,&r);
            if(r<min)
                min = r;
            if(r>max)
                max = r;            
        }
    }

    //use the formula of normalization
    double scale = 255.0/(max-min);
    
    for(int i = 0; i < img->w ; i++)
    {
        for(int j = 0; j < img->h; j++)
        {
            pix = getpixel(img,i,j);
            SDL_GetRGB(pix,img->format,&r,&r,&r);

            r -= min;
            r *= scale;
            pix = SDL_MapRGB(img->format,r,r,r);
            putpixel(img,i,j,pix);        
        }
    }
    
}

void equalize(SDL_Surface *img)
{
    long hist[256] = {0};
    Uint32 pix;
    Uint8 r = 0;
    
    // historigramme
    for(int i = 0; i < img->w ; i++)
    {
        for(int j = 0; j < img->h; j++)
        {
            pix = getpixel(img,i,j);
            SDL_GetRGB(pix,img->format,&r,&r,&r);
            hist[r]++;                   
        }
    }
    //cumul of historigramme
    for(size_t i = 1;i<256;i++)
        hist[i] += hist[i-1];


    for(int i = 0; i < img->w ; i++)
    {
        for(int j = 0; j < img->h; j++)
        {
            pix = getpixel(img,i,j);
            SDL_GetRGB(pix,img->format,&r,&r,&r);
            r = hist[r] * 255/(img->w*img->h);
            pix = SDL_MapRGB(img->format,r,r,r);
            putpixel(img,i,j,pix);                 
        }
    } 
}




void segIm(SDL_Surface *img)
{
    Uint8 Cr , Cb, r, g, b;
    Uint32 pix;
    for(int i = 0; i < img->w ; i++)
    {
        for(int j = 0; j < img->h; j++)
        { 
            pix = getpixel(img,i,j);
            SDL_GetRGB(pix,img->format,&r,&g,&b);
            Cr = 0.5 *r-0.4187*g-0.0813*b +128;
            Cb = -0.1687*r-0.3313*g+0.5*b + 128;
            
            if(((Cb >= 85) & (Cb<=135)) & ((Cr>=135)&&(Cr<=180)))
            {
                pix = SDL_MapRGB(img->format,255,255,255);
                putpixel(img,i,j,pix); 
            }
            else
            {
                pix = SDL_MapRGB(img->format,0,0,0);
                putpixel(img,i,j,pix);
            }
        }
    }
}

int sum_square(int **arr,int x, int y, int w)
{
    return arr[x][y]+arr[x+w][y+w]-arr[x][y+w]-arr[x+w][y];
}
void face(int **arr,int *x,int *y,int *c,int weight, int height)
{
    int max = 0, sum = 0;
    for(int i = 0;i<weight;i++)
    {
        for(int j  = 0;j<height;j++)
        {
            for(int w = 0;(j+w+1<height)&(i+w+1<weight);w++)
            {
                sum = sum_square(arr,i,j,w);
                if(sum>max)
                {
                    max = sum;
                    *x = i;
                    *y = j;
                    *c = w;
                }
                
            }
        }
    }               

}


int** imgToArrayFace(SDL_Surface* img) {
	int **arr;
	arr = malloc(img->w * sizeof(int*));
	for(int i = 0; i < img->w; i++)
		arr[i] = malloc(img->h * sizeof(int));

	for(int i = 0; i < img->w; i++) {
		for(int j = 0; j < img->h; j++) {
            if(!(getpixel(img, i, j)))
                arr[i][j] = -1;
            else
                arr[i][j] = 1;        
		}
	}
	return arr;
}


void square(SDL_Surface *img,int x,int y, int w)
{   
    Uint32 pix;
    int xw = x+w , yw = y +w, initx = x,inity = y;
    for(;x<=xw;x++)
    {
        pix = SDL_MapRGB(img->format,0,255,0);
        putpixel(img,x,y,pix);
    }
    for(;y<=yw;y++)
    {
        pix = SDL_MapRGB(img->format,0,255,0);
        putpixel(img,x,y,pix);
    }
    x = initx;
    y = inity;
    for(;y<=yw;y++)
    {
        pix = SDL_MapRGB(img->format,0,255,0);
        putpixel(img,x,y,pix);
    }
    for(;x<=xw;x++)
    {
        pix = SDL_MapRGB(img->format,0,255,0);
        putpixel(img,x,y,pix);
    }
}
