
/* [c] piotao, 20170318, @hebron
 * program wyciągający wybraną linię z obrazu i zapisujący ją jako dane
 * getScanLine -x 25  -r -i obrazek.png -o red.dat  - wyciąga kanał R z 25 poziomej linii pikseli
 * getScanLine -y 100 -b -i obrazek.png -o blue.dat - wyciąga kanał niebieski setnej linii pionowej
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "pixels.h"
#include "vector.h"

int BYTE3 = 0x00ff0000;
int BYTE2 = 0x0000ff00;
int BYTE1 = 0x000000ff;

const char DIR = 'x';

int R = 0;
int B = 0;
int G = 0;
int X = -1;
int Y = -1;

char* OUT = "-";
char* INP;

void scanandwrite(FILE *F,SDL_Surface *I,const char dir,int N,char ch,const char* name,const char* text){
	int i;
	pVector V = NULL;
	if(dir == 'x') V = hscanlineV(I,N,ch);
	else V = vscanlineV(I,N,ch);
	fprintf(F,text,N,name);
	for(i=0;i<V->size;i++) fprintf(F,"%f\n",V->T[i]);
	freeVector(V);
}

int main(int argc, char** argv){
	int i=1,rgb=-1;
	SDL_Surface *image;
	FILE *fout;

	while(i<argc){
		if(!strcmp("-x",argv[i])){ X = atoi(argv[++i]); }
		if(!strcmp("-y",argv[i])){ Y = atoi(argv[++i]); }
		if(!strcmp("-r",argv[i])){ R = 1; }
		if(!strcmp("-g",argv[i])){ G = 1; }
		if(!strcmp("-b",argv[i])){ B = 1; }
		if(!strcmp("-o",argv[i])){ OUT = argv[++i]; }
		if(!strcmp("-i",argv[i])){ INP = argv[++i]; }
		i++;
	}
	image = IMG_Load(INP);
	if(image){
		if(!strcmp("-",OUT)){ fout = stdout; }
		else if( (fout = fopen(OUT,"w")) ){
			if(X>=0 && Y>=0){ /* both coords given, only ONE pixel fetch! */
				fprintf(fout,"# R,G,B,(int)  -- pixel from %s, xy: %i %i\n",OUT,X,Y);
				rgb = getpixel(image,X,Y);
				fprintf(fout,"%i %i %i %i\n", (rgb & BYTE3)>>16, (rgb & BYTE2)>>8, (rgb & BYTE1), rgb );
			}
			else{
				if(X<0){ /* Y is to fetch, horizontal!!! */
					if(R) scanandwrite(fout,image,'x',Y,'r',INP,"# red channel from %i row, pix: %s\n");
					if(G) scanandwrite(fout,image,'x',Y,'g',INP,"# green channel from %i row, pix: %s\n");
					if(B) scanandwrite(fout,image,'x',Y,'b',INP,"# blue channel from %i row, pix: %s\n");
				}
				else{ /* X is to fetch, vertical!!! */
					if(R) scanandwrite(fout,image,'y',X,'r',INP,"# red channel from %i column, pix: %s\n");
					if(G) scanandwrite(fout,image,'y',X,'g',INP,"# green channel from %i column, pix: %s\n");
					if(B) scanandwrite(fout,image,'y',X,'b',INP,"# blue channel from %i column, pix: %s\n");
				}
			}
			fclose(fout);
		}
		else{
			fprintf(stderr,"Can't write to file: %s!\n",OUT);
		}
	}

	SDL_FreeSurface(image);

	return 0;
}

