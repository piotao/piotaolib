
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 *
 * 20170223:pio: included to piotaolib library, created before 2010
 */

#include <math.h>

#include "defs.h"
#include "matrix.h"

/* create new dynamic matrix structure */
pMatrix newMatrix(int w, int h) {
	pMatrix T = (pMatrix) malloc(sizeof(Matrix));
	T->W = w;
	T->H = h;
	T->M = T->W * T->H * sizeof(Data);
	T->T = (T->M) ? (pData) calloc((size_t)w * h,(size_t) sizeof(Data)) : NULL; /* do not allocate for 0-sized matrixes */
	return T;
}

/* this is special - it creates matrix, WITHOUT any DATA, just a container for pData buffer */
pMatrix newNoMatrix(int w, int h){
	pMatrix T = (pMatrix) malloc(sizeof(Matrix));
	T->W = w;
	T->H = h;
	T->M = T->W * T->H * sizeof(Data);
	T->T = NULL;
	return T;
}

/* create matrix from vector, missing data is filled with zeros */
pMatrix fromVector(int w, int h, pVector V){
	pMatrix T = newMatrix(w,h);
	if(V){
		int v = 0;
		for(int i=0;i<T->W;i++)
			for(int j=0;j<T->H;j++){
				setElement(T,i,j, v<V->size ? V->T[v++] : ZERO);
			}
	}
	return T;
}

/* deallocates matrix memory, this destroys it */
void freeMatrix(pMatrix M) {
	if (M) {
		if(M->T) free(M->T);
		free(M);
	}
}

/* deallocates matrix memory, this destroys it, but OMITs internal data, it should be freed separately */
void freeNoMatrix(pMatrix M) {
	if (M) {
		free(M);
	}
}

/* set single element of the matrix */
void setElement(pMatrix M,int i,int j,Data data){
	*(M->T+i*M->H+j) = data;
}

/* changes the location of two elements, by swapping them */
void swapElement(pMatrix M, int a,int b,int c,int d){
	pData idx1,idx2;
	Data tmp;
	if(M){
		idx1 = M->T+a*M->H+b;
		idx2 = M->T+c*M->H+d;
		tmp = *idx1;
		*idx1 = *idx2;
		*idx2 = tmp;
	}
}

/* get single element from the matrix */
Data getElement(pMatrix M,int i,int j){
	return *(M->T+i*M->H+j);
}

/* get whole horizontal vector from matrix */
pVector getVectorRow(pMatrix M,int y){
	pVector H = NULL;
	if(M){
		H = newVector(M->W);
		for(int i=0; i<H->size; i++) H->T[i] = getElement(M,i,y);
	}
	return H;
}

/* get whole vertical vector from matrix */
pVector getVectorCol(pMatrix M,int x){
	pVector V = NULL;
	if(M){
		V = newVector(M->H);
		for(int i=0; i<V->size; i++) V->T[i] = getElement(M,x,i);
	}
	return V;
}

/* set matrix to any specific value */
void setMatrix(pMatrix M, Data data) {
	if (M) {
		int i, j;
		for (i = 0; i < M->W; i++)
			for (j = 0; j < M->H; j++)
				setElement(M,i,j,data);
	}
}

/* sets fragment of matrix to specified data */
void setSubMatrix(pMatrix M,int x, int y,int w, int h, Data data){
	int i,j;
	if(M){
		for(i=0; i<w; i++)
			for(j=0; j<h; j++)
				setElement(M, i+x, j+y, data);
	}
}

/* fills matrix with increasing data starting from start */
void setMatrixInc(pMatrix M, Data start){
	int i,size = 0;
	Data d = start;
	if(M){
		size = M->W * M->H;
		for(i=0; i<size; i++){
			M->T[i] = d;
			d += (Data) 1.0;
		}
	}
}

/* compare sizes like cmp(A-B): -1 for A<B, 0 for A==B, 1 for A>B */
int cmpW(pMatrix A,pMatrix B){
	if(!A && B) return -1;
	if(A && !B) return 1;
	if(!A && !B)return 0;
	return CMP(A->W,B->W);
}

int cmpH(pMatrix A,pMatrix B){
	if(!A && B) return -1;
	if(A && !B) return 1;
	if(!A && !B)return 0;
	return CMP(A->H,B->H);
}

/* cmp size: -1 for equal, but transposed, 0 for not equal, 1 for equal */
int cmpSize(pMatrix A, pMatrix B){
	if(!A || !B) return 0;
	if(A->W==B->W && A->H==B->H) return 1;
	if(A->W==B->H && A->H==B->W) return -1;
	return 0;
}

/* set matrix like B := A, the dimensions have to equal */
void cpMatrix(pMatrix B, pMatrix A) {
	if (A && B && cmpSize(A,B)) {
		int i, j;
		for (i = 0; i < B->W; i++)
			for (j = 0; j < B->H; j++)
				setElement(B,i,j,getElement(A,i,j));
	}
}

/* create matrix from another matrix: new B = A */
pMatrix fromMatrix(pMatrix A){
	pMatrix B = NULL;
	if(A){
		B = newMatrix(A->W,A->H);
		cpMatrix(B,A);
	}
	return B;
}

/* create matrix from submatrix given as wh at xy */
pMatrix fromSubMatrix(pMatrix A,int x,int y,int w,int h){
	pMatrix B = NULL;
	if(A){
		B = newMatrix(w,h);
		for(int i=0; i<w; i++)
			for(int j=0; j<h; j++)
				setElement(B,i,j,getElement(A,x+i,y+j));
	}
	return B;
}

/* adding matrixes: T = A+B, size have to equal! */
void addMatrix(pMatrix T, pMatrix A, pMatrix B) {
	if (A && B) {
		int i, j;
		if(!T) T = newMatrix(A->W,B->H);
		for (i = 0; i < A->W; i++)
			for (j = 0; j < B->H; j++)
				setElement(T,i,j,getElement(A,i,j)+getElement(B,i,j));
/*		alternative version (maybe faster): */
/*				*(T->T + i * T->W + j) = *(A->T + i * A->W + j) + *(B->T + i * B->W + j); */
	}
}

/* adding like reduce: new T = A+B, the safest way! */
pMatrix sumMatrix(pMatrix A,pMatrix B){
	pMatrix T = NULL;
	if(A && B){                             /* A and B */
		T = newMatrix(A->W,B->H);
		addMatrix(T,A,B);
	}
	else if(A && !B) return fromMatrix(A);  /* A and NULL */
	else if(!A && B) return fromMatrix(B);  /* NULL and B */
	return T;                               /* NULL and NULL */
}

void _Mul(pMatrix T,pMatrix A,pMatrix B){
	int i, j, k;
	for (i = 0; i < A->W; i++){
		for (j = 0; j < B->H; j++) {
			Data sum = (Data) 0.0;
			for (k = 0; k < A->H; k++) sum += getElement(A,i,k) * getElement(B,k,j);
			setElement(T,i,j,sum);
		}
	}
}

void mulMatrixRef(pMatrix T, pMatrix A, pMatrix B) {
	if (A && B) {
		if(!T) T = newMatrix(A->W,B->H);
		else{
			if(T->W!=A->W || T->H!=B->H){
				freeMatrix(T);
				T = newMatrix(A->W,B->H);
			}
		}
		_Mul(T,A,B);
	}
}

/* TODO: check and benchmark this one */
void mulMatrixRefFast(register pMatrix T,register pMatrix A,register pMatrix B){
	register int i, j, k;
	register Data sum;
	for (i = 0; i < A->W; i++){
		for (j = 0; j < B->H; j++) {
			sum = (Data) 0.0;
			for (k = 0; k < A->H; k++) sum += *(A->T+i*A->H+k) * *(B->T+k*B->H+j);
			*(T->T+i*T->H+j) = sum;
		}
	}
}

/* a bit improved version of matrix multiplication: new T = A*B */
pMatrix mulMatrixNew(pMatrix A, pMatrix B) {
	pMatrix T = NULL;
	if (A && B) {
		T = newMatrix(A->W,B->H);
		_Mul(T,A,B);
	}
	return T;
}

/* printing matrix with given format for each point */
void printMatrixFmt(const char* fmt, pMatrix T) {
	if (T) {
		int i, j;
		for (i = 0; i < T->W; i++){
			for (j = 0; j < T->H; j++)
				printf(fmt, getElement(T,i,j));
			printf("\n");
		}
	}
	else
		printf("NULL\n");
}

/* printing matrix with %1.1f default format */
void printMatrix(pMatrix T) {
	const char* fmt = "%1.1f ";
	printMatrixFmt(fmt,T);
}

