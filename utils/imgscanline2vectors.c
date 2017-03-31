
/* [c] piotao, 20170331, @p109-12, 4piotaolib
 * Tool for conversion image -> data values stored
 * as single vertical vectors. Each vector contain
 * a horizontal line from the image.
 * Usage:
 *   imgscanline2vectors image.png
 * Output:
 *   lots of files with names like 0001, 0212, etc.
 *   where each contain a vector with data from the
 *   image, normalized to 0-1
 */

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "files.h"
#include "vector.h"
#include "pixels.h"


int main(int argc, char** argv){
	SDL_Surface *image = NULL;
	pVector V  = NULL;
	char* name = NULL;
	FILE* f    = NULL;
	char* frm  = "%i";
	char* fname= "%i";
	int i,j;

	if(argc<=1){
		fprintf(stderr,"Usage: %s image\n",argv[0]);
		exit(1);
	}

	image = IMG_Load(name);
	if(image){
		for(i=0;i<image->h;i++){
			V = hscanlineV(image,i,'r');
			if(V){
				sprintf(fname,frm,i);
				f = openFileToWrite(fname);
				if(f){
					fprintf(f,"# data points from horizontal line at y=%i\n",i);
					for(j=0;j<V->size;j++)
						fprintf(f,"%f\n",V->T[i]);
					fclose(f);
				}
				freeVector(V);
			}
		}
		SDL_FreeSurface(image);
	}
	return 0;
}
