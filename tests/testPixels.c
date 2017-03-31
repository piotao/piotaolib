
/*
 * [c] piotao, 20170318, @hebron
 * program testujący bibliotekę pixels, który umie wyciągnąć wiersz z obrazka
 * i wypisać go w postaci liczb. Argumenty:
 * t-pixels obrazek.png y
 * y to numer linii pixeli poziomych do wypisania, wypisywane są 3 kolumny
 * dla danych typu R G B
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "pixels.h"
#include "vector.h"

int main(int argc, char** argv){
	int i,y = 64;
	SDL_Surface *image;

	image = IMG_Load(argv[1]);
	if(argc>1) y = atoi(argv[2]);

	pVector Vr = hscanlineV(image,y,'r');
	pVector Vg = hscanlineV(image,y,'g');
	pVector Vb = hscanlineV(image,y,'b');

	printf("# picture: %s, line %i, RGB data\n",argv[1],y);
	for(i=0;i<Vr->size;i++){
		printf("%f %f %f\n",Vr->T[i],Vg->T[i],Vb->T[i]);
	}

	SDL_FreeSurface(image);
	freeVector(Vr);
	freeVector(Vg);
	freeVector(Vb);

	return 0;
}
