
#include <stdlib.h>
#include <stdio.h>

#include "numerics.h"
#include "pixels.h"
#include "options.h"
#include "files.h"

int WIND = 5;  // -w N   - window size on both sides
int X = -1;    // -x col - column for dump variance
int Y = -1;    // -y row - row for dump variance

int main(int argc, char** argv){
	char *name= NULL;
	pMatrix M = NULL;
	pVector V = NULL;
	CONF=CONF;
	newConfig(
		newItem("wind","-w",tINT,newInt(WIND),
		newItem("name","-f",tCHAR,newString(64),
		newItem("X",   "-x",tINT,newInt(X),
		newItem("Y",   "-y",tINT,newInt(Y),NULL))))
	);
	X = getConfAsInt("X");
	Y = getConfAsInt("Y");
	name = getConfAsStr("name");
	printf("name: %s, wind:%i, col:%i, row:%i\n",name,WIND,X,Y);
	if(fileExists(name)){
		M = decodeImage(name);
		V = getVectorCol(M,X);
		printf("# image: %s, column: %i, window: %i\n",name,X,WIND);
		printf("# data set: raw, variance\n");
		for(int i = 0; i<V->size; i++){
			printf("%f %f\n", V->T[i], varianceVectorAround1D(V,i,WIND));
		}
		freeMatrix(M);
		freeVector(V);
	}
	freeConfig(CONF);
	return 0;
}

