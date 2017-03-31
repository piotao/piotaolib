
#include <stdio.h>

#include "testing.h"
#include "matrix.h"
#include "numerics.h"

int main(){
	pMatrix M = newMatrix(3,3);
	pMatrix D = NULL;
	pMatrix G = NULL;

	// normal tests of simple things
	OK(" matrix is not NULL ", M != NULL );
	setElement(M,0,0,0.0); setElement(M,0,1,1.0); setElement(M,0,2,2.0);
	setElement(M,1,0,3.0); setElement(M,1,1,4.0); setElement(M,1,2,5.0);
	setElement(M,2,0,6.0); setElement(M,2,1,7.0); setElement(M,2,2,8.0);
	//printMatrix(M);
	isEQ(getElement(M,0,0),0.0); isEQ(getElement(M,0,1),1.0); isEQ(getElement(M,0,2),2.0);
	isEQ(getElement(M,1,0),3.0); isEQ(getElement(M,1,1),4.0); isEQ(getElement(M,1,2),5.0);
	isEQ(getElement(M,2,0),6.0); isEQ(getElement(M,2,1),7.0); isEQ(getElement(M,2,2),8.0);

	OK("sum matrix is 36\n",36.0 == reduceMatrix(M));
	OK("avefast matrix is 4\n",4.0 == averagefastMatrix(M));
	OK("ave matrix is 4\n",4.0 == averageMatrix(M));
//	printMatrix(M);
	D = fromSubMatrix(M,1,1,2,2);
//	printf("fromSubMatrix, W:%i, H:%i\n",D->W,D->H);
//	printMatrix(D);
//	printf("--------------\n");
	freeMatrix(D);

	setMatrix(M,1.1);
	isEQ(getElement(M,0,0),1.1); isEQ(getElement(M,0,1),1.1); isEQ(getElement(M,0,2),1.1);
	isEQ(getElement(M,1,0),1.1); isEQ(getElement(M,1,1),1.1); isEQ(getElement(M,1,2),1.1);
	isEQ(getElement(M,2,0),1.1); isEQ(getElement(M,2,1),1.1); isEQ(getElement(M,2,2),1.1);

	drand48Matrix(M);
	D = fromMatrix(M);

//	printMatrixFmt("%8.4f",M);
	flipMatrixH(M);
//	printMatrixFmt("%8.4f",M);
	isEQ(getElement(M,0,0),getElement(D,0,2));
	isEQ(getElement(M,1,0),getElement(D,1,2));
	isEQ(getElement(M,2,0),getElement(D,2,2));
	flipMatrixH(M);
	flipMatrixV(M);
//	printMatrixFmt("%8.4f",M);
	isEQ(getElement(M,0,0),getElement(D,2,0));
	isEQ(getElement(M,0,1),getElement(D,2,1));
	isEQ(getElement(M,0,2),getElement(D,2,2));

	freeMatrix(M);
	freeMatrix(D);

	M = newMatrix(5,5);
	D = newMatrix(3,3);

	setMatrix(M,1.0);
	setElement(M,2,2,5.0);
	setMatrix(D,0.0);
	setElement(D,1,1,2.0);
	printf("M:\n");printMatrix(M);
	printf("D:\n");printMatrix(D);

	//filtering
	printf("flter\n");
	pMatrix R = filterMatrix(D,M);
	printf("R:\n");printMatrix(R);
	freeMatrix(M);
	freeMatrix(D);
	freeMatrix(R);

	// gaussian
	G = makeGaussian(9,5.0);
	printf("average gaussian: %f\n",averageMatrix(G));
	mulMatrixBy(G,100.0);
	printMatrixFmt("%8.4f",G);
	freeMatrix(G);
	
	// vector:vector multiplication -> result scalar
	M = newMatrix(1,10); setMatrixInc(M,1.0);
	G = newMatrix(10,1); setMatrixInc(G,1.0);
	D = mulMatrixNew(M,G);
	printf("matrixM:\n");printMatrixFmt("%8.4f",M);
	printf("matrixG:\n");printMatrixFmt("%8.4f",G);
	printf("matrixD:\n");printMatrixFmt("%8.4f",D);
	freeMatrix(M);
	freeMatrix(G);
	freeMatrix(D);

	// vector:vector multiplication -> result matrix
	M = newMatrix(10,1); setMatrixInc(M,1.0);
	G = newMatrix(1,10); setMatrixInc(G,1.0);
	D = mulMatrixNew(M,G);
	printf("matrixM:\n");printMatrixFmt("%8.4f",M);
	printf("matrixG:\n");printMatrixFmt("%8.4f",G);
	printf("matrixD:\n");printMatrixFmt("%8.4f",D);
	freeMatrix(M);
	freeMatrix(G);
	freeMatrix(D);

	M = newMatrix(7,7);
	setSubMatrix(M,2,2,3,3,1.0);
	setSubMatrix(M,3,3,1,1,2.0);
	G = makeGaussian(2,2.0);
//	setElement(G,0,0,0.0); setElement(G,0,1,1.0); setElement(G,0,2,0.0);
//	setElement(G,1,0,1.0); setElement(G,1,1,2.0); setElement(G,1,2,1.0);
//	setElement(G,2,0,0.0); setElement(G,2,1,1.0); setElement(G,2,2,0.0);
	D = filterMatrix(G,M);
	printf("matrixM:\n");printMatrixFmt("%8.4f",M);
	printf("matrixG:\n");printMatrixFmt("%8.4f",G);
	printf("matrixD:\n");printMatrixFmt("%8.4f",D);
	freeMatrix(M);
	freeMatrix(G);
	freeMatrix(D);
	return 0;
}

