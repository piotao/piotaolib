
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 *
 * Library to fetch pixel data from images, using SDL library
 *
 * 20170310,pio: created @soar for piotaolib
 * 20170321,pio: added vscanlineV, fixes in hscanlineV
 * 20170322,pio: added decodeImage
 */


#include "stdlib.h"
#include "stdio.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_error.h"

#include "data.h"
#include "listd.h"
#include "pixels.h"

/* fetches pixel as RGBA from xy */
/* int pixel = getpixel(image,23,34);  pixel contains 4bytes color code */
int getpixel(SDL_Surface *surface,int x,int y){
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y*surface->pitch + x*bpp;
	switch(bpp){
		case 1: return (int)*p; break;
		case 2: return (int)(*(Uint16*)p); break;
		case 3: if(SDL_BYTEORDER == SDL_BIG_ENDIAN) return (int)(p[0]<<16|p[1]<<8|p[2]);
						else return (int)p[0]|p[1]<<8|p[2]<<16;
						break;
		case 4: return (int)(*(Uint32*)p); break;
		default: return 0;
	}
}

/* returns a list with RGB pixels from horizontal line */
/* pListD L = hscanline(image,23); */
/* pixels in the list are RGB structures */
pListD hscanlineL(SDL_Surface *image,int y){
	pListD L = NULL;
	if(image){
		L = newListD();
		pRGB P = NULL;
		for(int j=0;j<image->w;j++){
			P = (pRGB) malloc(sizeof(RGB));
			if(P){
				SDL_GetRGB( *((uint32_t*)image->pixels + y*image->w+j), image->format, &(P->r), &(P->g), &(P->b));
				insLast(L,(pvoid)P);
			}
			else{
				fprintf(stderr,"warn: P is NULL after malloc RGB in __FILE__!\nNot all data from scanline will be stored.");
			}
		}	
	}
	return L;
}

/* returns a vector of normalized, floating point data in range 0-1 from horizontal line, either r, g or b component */
/* usage: pVector R = hscanlineV(image,23,'r');   - gets red channel in vector Data */
pVector hscanlineV(SDL_Surface *image,int y,int color){
	pVector V = NULL;
	int i=0,pixel = 0;
	if(y<0) y = 0;
	if(image){
		if(y>image->w) y = image->w;
		V = newVector(image->w);
		for(i=0;i<image->w;i++){
			pixel = getpixel(image,i,y);
			if     (color=='r') V->T[i] = (Data) ((pixel>>16)&255);
			else if(color=='g') V->T[i] = (Data) ((pixel>>8 )&255);
			else if(color=='b') V->T[i] = (Data) ((pixel&255));
			else V->T[i] = (Data) pixel;
			V->T[i] /= 255;  /*normalization to 0-1 range!*/
		}
	}
	return V;
}

/* returns a vector of normalized, floating point data in range 0-1 from a vertical line */
/* taken from a picture in column y, as a single channel, either 'r', 'g' or 'b'. */
pVector vscanlineV(SDL_Surface *image,int x,int color){
	pVector V = NULL;
	int i=0, pixel = 0;
	if(x < 0) x = 0;
	if(image){
		if(x>image->h) x = image->h;
		V = newVector(image->h);
		for(i=0;i<image->h;i++){
			pixel = getpixel(image,x,i);
			if     (color == 'r') V->T[i] = (Data) ((pixel>>16)&255);
			else if(color == 'g') V->T[i] = (Data) ((pixel>>8 )&255);
			else if(color == 'b') V->T[i] = (Data) ((pixel & 255));
			else V->T[i] = (Data) pixel;
			V->T[i] /= 255; /* normalization to 0-1 range */
		}
	}
	return V;
}

pMatrix decodeImage(char *name){ /* reads all scanlines */
	SDL_Surface *image = NULL;
	pMatrix M = NULL;

	image = IMG_Load(name);
	if(image){
		M = newMatrix(image->w, image->h);
		for(int i=0; i<M->W; i++)
			for(int j=0; j<M->H; j++){
				int pixel = getpixel(image,i,j);
				setElement(M,i,j, (Data) ((pixel & 255) / 255.0) );
			}
		SDL_FreeSurface(image);
	}
	return M;
}

