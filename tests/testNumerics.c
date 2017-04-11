
#include <stdio.h>
#include "vector.h"
#include "numerics.h"

int main(){

	/*
	pVector V = defVector(
		-666.0,
		0.0, 0.0, 1.0, 0.0, 0.0,
		0.0, 1.0, 2.0, 1.0, 0.0,
		1.0, 2.0, 5.0, 2.0, 1.0,
		0.0, 1.0, 2.0, 1.0, 0.0,
		0.0, 0.0, 1.0, 0.0, 0.0,
		-666.0
	);
	printf("V:"); printVectorFmt("%f;",V); printf("\n");
	pMatrix M = fromVector(5,5,V);
	printf("M:\n");	printMatrix(M); printf("\n");
	
	Data varv = varianceVector(V->T,V->size);
	Data varm = varianceMatrix(M);
	printf("varv=%f\nvarm=%f\n",varv,varm);
*/
	pMatrix M = newMatrix(10,10);	drand48Matrix(M); //setMatrix(M,1.0); setElement(M,2,2,2.0); //setMatrixInc(M,1.0);
	printf("M:\n");	printMatrixFmt("%6.1f",M); printf("\n");

	//pMatrix S = fromSubMatrix(M,1,2,3,3);
	//printf("S:\n");printMatrix(S);printf("\n");
	printf("vars:%f\n",varianceSubMatrix(M,4,4,2,2));
	//freeVector(V);
	for(int i=0;i<M->W;i++){
		for(int j=0;j<M->H;j++){
			printf("%8.2f ", varianceSubMatrix(M,i,j,4,4));
		}
		printf("\n");
	}
	freeMatrix(M);
	//freeMatrix(S);

	return 0;
}
