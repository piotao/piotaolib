
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
inline int clamp(int low,int n,int top){ return n<low? n : n<top ? n : top; }
Data maxData(pData T,int SIZE);
Data minData(pData T,int SIZE);
Data medianData(pData T,int SIZE);
Data findListMax(pListD L);
Data maxVector(pVector V);
Data minVector(pVector V);

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

/* misc matrix computations functions */
pMatrix transposeMatrix(pMatrix A);
void mulMatrixBy(pMatrix A,Data scalar);
void flipMatrixH(pMatrix A);
void flipMatrixV(pMatrix A);
Data reduceMatrix(pMatrix A);
pMatrix makeGaussian(int radius,Data sigma);
pMatrix filterMatrix(pMatrix F, pMatrix M);

/* simple algebra functions on flat vectors */
void addData(pData T,int SIZE,Data val);
pData addDataData(pData T1,pData T2,int SIZE);
pData subDataData(pData T1,pData T2,int SIZE);
void absData(pData T,int SIZE);
Data reduceSumData(pData T,int SIZE);
Data reduceMulData(pData T,int SIZE);
Data reduceSQsumData(pData T,int SIZE);
void saxpy(pData T,int SIZE,Data a,Data b);
pData mulDataHadamard(pData T1,pData T2,int SIZE);



#endif

