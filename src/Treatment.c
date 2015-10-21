#include<stdlib.h>
#include<stdio.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include"IntegralImage.h"


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

void image_to_grey(SDL_Surface *img)
{   
     Uint8 r = 0,g = 0,b = 0;
     Uint32 pix = 0;
     float lum = 0.0;
     for(int i = 0; i < img->w ; i++)
     {
         for(int j = 0; j < img->h; j++)
         {
             pix = getpixel(img,i,j);
             SDL_GetRGB(pix, img->format,&r,&g,&b);
             lum = (0.2126 * r + 0.7152  * g + 0.0722  * b)/3;
             r  = g = b = lum;
             pix = SDL_MapRGB(img->format, r, g, b);
             putpixel(img, i, j, pix);
         }
    }
}








