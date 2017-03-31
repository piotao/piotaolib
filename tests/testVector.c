
#include <stdio.h>
#include "defs.h"
#include "vector.h"
#include "numerics.h"

int main(){

	pVector H = NULL;
	pVector V = newNoVector(10);

	V->T = defData(1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0);
	printVector(V);printf("\n");
	reverseVector(V);
	printVector(V);printf("\n");
	reverseVector(V);
	printVector(V);printf("\n");

	H = newCopyVectorFromTo(V,4,6);
	printVector(H);
	freeVector(V);
	freeVector(H);
	return 0;

}
