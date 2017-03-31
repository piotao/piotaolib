
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "defs.h"
#include "data.h"
#include "listd.h"
#include "numerics.h"

int main(){

	/* test uśredniania listyd */
	/*
	pData T = NULL;
	pData d1,d2,d3;
	pListD L = NULL;
	d1 = (pData)malloc(sizeof(Data));
	d2 = (pData)malloc(sizeof(Data));
	d3 = (pData)malloc(sizeof(Data));
	*d1 = 0.0; *d2 = 2.0; *d3 = 4.0;
	L = defListD( (pvoid)d1 );
	insLast(L, (pvoid)d2 );
	insLast(L, (pvoid)d3 );
	printListD(L);
	printf("average: %f\n", averageList(L));
	freeListD(L);
	free(d1); free(d2); free(d3);
	*/

	/* test uśredniania danych w wektorze */
	/*
	pData T = NULL;
	Data a = ZERO;
	T = defData(1.0,2.0,3.0,4.0,5.1);
	printData(T,5);
	printf("average from T: %f\n",averageVector(T,5));
	a = averageVectorFromTo(T,4,-2);
	printf("ave from 2 to 4: %f\n",a);
	freeData(T);
	*/

	/* test uśredniania macierzy */
	pMatrix M = NULL;
	M = newMatrix(3,3);
	srand48(time(NULL));
	//drand48Matrix(M);
	//randMatrix(M);
	setElement(M,0,0,1.0); setElement(M,0,1,2.0); setElement(M,0,2,3.0);
	setElement(M,1,0,4.0); setElement(M,1,1,5.0); setElement(M,1,2,6.0);
	setElement(M,2,0,7.0); setElement(M,2,1,8.0); setElement(M,2,2,9.0);
	printMatrixFmt("%g ",M);
	printf("ave: %f\n",averageMatrix(M));
	printf("aveFromTo: %f\n",averageSubMatrix(M,1,0, 2,3));
	freeMatrix(M);


	return 0;
}

