
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 *
 * 20170223:pio: included to piotaolib library, created before 2010
 * 20170306:pio: main code refactoring and split to h and c files.
 * 20170315:pio: comment style changed to conform C90 ansi standard
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <values.h>

#include "defs.h"
#include "vector.h"
#include "matrix.h"

/* MATRIX 2D structure */
typedef struct Matrix {
	int W;    /* dimension X */
	int H;    /* dimension Y */
	int M;    /* memory occupied: W*H*sizeof(Data) */
	pData T;  /* simple pointer to linear data buffer */
} Matrix;

/* pointer to matrix2d struct */
typedef Matrix* pMatrix;

#define CMP(x,y) ((x)<(y)?-1:((x)>(y))?1:0)

pMatrix newMatrix(int w, int h);
pMatrix newNoMatrix(int w, int h);
pMatrix fromMatrix(pMatrix A);
pMatrix fromSubMatrix(pMatrix A,int x,int y,int w,int h);
void freeMatrix(pMatrix M);
void freeNoMatrix(pMatrix M);

void setElement(pMatrix M,int i,int j,Data data);
Data getElement(pMatrix M,int i,int j);
void swapElement(pMatrix M, int a,int b,int c,int d);
pVector getVectorRow(pMatrix M,int y);
pVector getVectorCol(pMatrix M,int x);

void setMatrix(pMatrix M, Data data);
void setSubMatrix(pMatrix M,int x, int y,int w, int h, Data data);
void setMatrixInc(pMatrix M,Data start);

int cmpW(pMatrix A,pMatrix B);
int cmpH(pMatrix A,pMatrix B);
int cmpSize(pMatrix A, pMatrix B);
void cpMatrix(pMatrix B, pMatrix A);

void addMatrix(pMatrix T, pMatrix A, pMatrix B);
pMatrix sumMatrix(pMatrix A,pMatrix B);
void _Mul(pMatrix T,pMatrix A,pMatrix B);
void mulMatrixRef(pMatrix T, pMatrix A, pMatrix B);
void mulMatrixRefFast(register pMatrix T,register pMatrix A,register pMatrix B);
pMatrix mulMatrixNew(pMatrix A, pMatrix B);

void printMatrixFmt(const char* fmt, pMatrix T);
void printMatrix(pMatrix T);

#endif

