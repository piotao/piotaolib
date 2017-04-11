
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 *
 * 20100422, by piotao, @hebron
 * 20170306: split style refactoring
 * 20170327,pio: added to piotaolib
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include "defs.h"
#include "data.h"

/* simple data vector to keep them all like in an array */
typedef struct {
	int size;			/* maximum length of data buffer */
	pData T;			/* data buffer by itself */
} Vector;

/* pointer to Vector data buffer */
typedef Vector* pVector;

pVector newVector(int size);
pVector newNoVector(int size);
pVector defVector(Data d,...);
pVector newCopyVector(pVector V);
pVector newCopyVectorFromTo(pVector V,int start,int end);
pVector newFromData(pData T,int SIZE);
pVector newFromVectors(pVector P,pVector Q);
void swapElementV(pVector V, int a,int b,int c,int d);
void freeVector(pVector V);
void freeNoVector(pVector V);
void printVector(pVector V);
void printVectorN(pVector V,int count);
void printlnVectorN(pVector V,int count);
void printVectorFmt(const char* format,pVector V);

#endif /* VECTOR_H_ */

