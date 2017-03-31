
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 *
 * Library to fetch pixel data from images, using SDL library
 *
 * 20170310,pio: created for piotaolib
 * 20170321,pio: added vscanlineV, fixes in hscanlineV
 * 20170322,pio: added decodeImage
 */

#ifndef __PIO_PIXELS_
#define __PIO_PIXELS_

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_error.h"

#include "listd.h"    /* for hscanlineL */
#include "vector.h"   /* for *lineV */
#include "matrix.h"   /* for decodeImage */

typedef struct RGB {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} RGB;
typedef RGB* pRGB;

int getpixel(SDL_Surface *surface,int x,int y);  /* fetches pixel as RGBA from xy */
pListD hscanlineL(SDL_Surface *image,int y);     /* returns a list with RGB pixels from horizontal line */
pVector hscanlineV(SDL_Surface *image,int y,int color); /* returns a vector or data from horizontal line, either r, g or b component */
pVector vscanlineV(SDL_Surface *image,int x,int color); /* returns a vector or data from vertical line, either r, g or b component */
pMatrix decodeImage(char *name); /* reads all scanlines */

#endif
