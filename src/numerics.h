
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 * Moved here are:
 * average.h, origin from: 20170310, by piotao
 * norm.h, origin from: 20170310, by piotao
 * maxmin.h, origin from 201703~, by piotao
 * variance.h, origin from 201703~, by piotao
 */

#ifndef __PIOTAOLIB_NUMERICS
#define __PIOTAOLIB_NUMERICS

#include "defs.h"    /* basic generic types definitions */
#include "listd.h"   /* for operations on d-list */
#include "vector.h"  /* 1d-vectors handling */
#include "matrix.h"  /* 2d-matrices definiton */

/* average functions working on vectors and matrices (former average.h) */
Data averageVector(pData T,int SIZE);
Data averageVectorFromTo(pData T,int start,int end);
Data averageVectorToFrom(pData T,int start,int end);
Data averageList(pListD L);
Data averagefastMatrix(pMatrix A);
Data averageMatrix(pMatrix M);
Data averageSubMatrix(pMatrix M,int x,int y,int w,int h);

/* data normalization working on verctors and matrices (former norm.h) */
pData normalizeData(pData T,int SIZE,Data max);
pData normalizeDataFromTo(pData T,int start,int end,Data max);
pListD normalizeList(pListD L);
//TODO void normalizeMatrix(pMatrix M);


/* data search and lookup */
inline int max(int a,int b){ return (a>b)?a:b; }
inline int min(int a,int b){ return (a<b)?a:b; }
inline int torange(int low,int n,int top){ return n<low? n : n<top ? n : top; }
Data maxData(pData T,int SIZE);
Data minData(pData T,int SIZE);
Data medianData(pData T,int SIZE);
Data findListMax(pListD L);


/* variance related functions */
Data varianceDataFromTo(pData T,int start,int end);
pData varianceVectorWindow(pData T,int size,int wind);
Data varianceVector(pData T,int n);
Data varianceVectorAround1D(pVector V, int n, int wind);
Data varianceMatrix(pMatrix M);
Data varianceSubMatrix(pMatrix M,int x,int y,int w,int h);

/* utility functions, unrelated to numerics */
long int getmicrosecond();

/* non-standard vector operations */
pData randomizeData(pData T,int n);
pData generateData(pData T,int n,Data (*f)(int));
void randomizeVector(pVector V);
pVector reverseVector(pVector V);
void randomizeMatrix(pMatrix M);
void drand48Matrix(pMatrix M);

/* make transpose matrix A to new matrix which is created and returned */
pMatrix transposeMatrix(pMatrix A);
/* multiplies matrix by a scalar value */
void mulMatrixBy(pMatrix A,Data scalar);
/* flips matrix horizontally and returns the new matrix */
void flipMatrixH(pMatrix A);
/* flips matrix vertically and returns the new matrix */
void flipMatrixV(pMatrix A);
/* sum the whole matrix */
Data reduceMatrix(pMatrix A);
/* prepare gaussian distribution for a flitering, matrix is (radius*2+1)² */
pMatrix makeGaussian(int radius,Data sigma);
/* makes filtering with the usage of matrix F over matrix M */
pMatrix filterMatrix(pMatrix F, pMatrix M);





#endif

