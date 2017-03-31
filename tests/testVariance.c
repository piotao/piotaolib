
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "vector.h"
#include "matrix.h"
#include "numerics.h"

int main(int argc, char** argv){

	int x,w;
	pVector V = defVector(-1000.0, 1.,1.,2.,3.,0.,1.,2.,3.,4., -1000.0);
	pVector W = defVector(-5.0,    1.,1.,1.,2.,3., -5.0);

	printf("variance[1 1 1 2 3]=%f\n",varianceVector(W->T,W->size));
	freeVector(W);

	x = 4; // data index
	w = 4; // window size on both sides
	printf("\nV->size:%i, x:%i, w:%i, var:%f\n",V->size,x,w,varianceVectorAround1D(V,x,w));

	x = 6;
	w = 2;
	printf("\nV->size:%i, x:%i, w:%i, var:%f\n",V->size,x,w,varianceVectorAround1D(V,x,w));

	freeVector(V);

	pMatrix M = newMatrix(5,5);
	setMatrix(M,1.0);
	setSubMatrix(M,0,0,3,3,0.0);
	setElement(M,1,1,9.0);
	setElement(M,0,0,1.0);
	printMatrixFmt("%8.4f",M);
//	printf("varM: %f\n",varianceMatrix(M));
	printf("varSubM: %f\n",varianceSubMatrix(M,0,0,2,2));

	freeMatrix(M);

	return 0;

}
