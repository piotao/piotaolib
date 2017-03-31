
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 */

#include <math.h>       /* functions like pow, exp, etc. */
#include <sys/time.h>   /* for gettimeofday for getmicrosecond */

#include "defs.h"       /* basic general data types */
#include "data.h"       /* basic vector and primitive handling */
#include "listd.h"      /* double-linked list implementation */
#include "matrix.h"     /* 2d-matrix handling */

#include "numerics.h"   /* header of this module */



/* AVERAGING FUNCTIONS */

/* averages the whole bare vector data using SIZE, starting from 0 */
Data averageVector(pData T,int SIZE){
	int i;
	Data ave = 0.0;
	Data sum = 0.0;
	if(T && SIZE>0){
		for(i=0;i<SIZE;i++) sum += T[i];
		ave = sum / SIZE;
	}
	return ave;
}

/* http://www.naukowiec.org/wzory/statystyka/wariancja_6.html */
/* calc the arithmetic average from a specified range for a vector 1d */
/* T = vector 1d */
/* start,end = range */
Data averageVectorFromTo(pData T,int start,int end){
  int i;
  Data sum = ZERO;
  Data ave = ZERO;
  if(T!=NULL && end-start>0){
    for(i=start; i<end; i++) sum += T[i];
    ave = sum / (end-start);
  }
  return ave;
}


/* averageVectorFromTo: calc average of the part of the vector using start:end coords
 * if start<end, then positive direction is used, if start>end the negative direction is used.
 * for data as: 1 2 3 4 5 6 and start=1,end=3 (data is 2 3 4) ave is 3.,
 * for data as: 1 2 3 4 5 6 and start=3,end=1 (data is 4 3 2) ave is 3.
 */
Data averageVectorToFrom(pData T,int start,int end){
	int i = 0,diff = 0;
	Data ave = ZERO;
	Data sum = ZERO;
	if(start < end){
		if(start < 0) start = 0;
		for(i=start;i<end;i++) sum += T[i];
		diff = end - start;
	}
	else if(start > end){  /* 1 2 3 4  s:4 e:2, i=4 3 2 */
		if(end < -1) end = -1;
		for(i=start;i>end;i--) sum += T[i];
		diff = start - end;
	}
	if(diff != 0) ave = sum / diff;
	else ave = NOTN;
	return ave;
}

/* average over double linked list */
Data averageList(pListD L){
	Data sum = 0.0;
	Data ave = 0.0;
	int count = 0;
	if(L && L->first){
		L->that = L->first;
		while(L->that != NULL){
			sum = sum + *((pData)(L->that->item));
			L->that = L->that->next;
			count++;
		}
		if(count>0) ave = sum / count;
		L->that = L->last;
	}
	return ave;
}

/* averaging the matrix using common approach */
Data averageMatrix(pMatrix M){
	Data ave = ZERO;
	Data sum = ZERO;
	int i,j;
	if(M){
		for(i=0; i<M->W; i++)
			for(j=0; j<M->H; j++){
				sum += getElement(M,i,j);
			}
		if(M->W*M->H != ZERO)
			ave = sum / (M->W*M->H);
		else
			ave = NOTN;
	}
	return ave;
}

/* fast average the whole matrix */
Data averagefastMatrix(pMatrix A){
	int i,size = 0;
	int sum=ZERO,ave=ZERO;
	if(A){
		size = A->W * A->H;
		for(i=0; i<size; i++)
			sum += *(A->T+i);
		ave = sum / size;
	}
	return ave;
}

/* calculates average matrix value given as submatrix with coords [x1,y1] and size [w,h] */
Data averageSubMatrix(pMatrix M,int x,int y,int w,int h){
	int i,j;
	Data ave = ZERO;
	Data sum = ZERO;
	if(M){
		for(i=x; i<x+w; i++){
			for(j=y; j<y+h; j++){
				printf("%f ",getElement(M,i,j));
				sum += getElement(M,i,j);
			}
		}
		ave = sum / (w*h);
	}
	return ave;
}



/* NORMALIZATION FUNCTIONS */

/* simply normalize the vector of data */
pData normalizeData(pData T,int SIZE,Data max){
	int i = 0;
	if(T && max != ZERO){
		for(i=0;i<SIZE;i++)
			T[i] /= max;
	}
	return T;
}

/* normalize vector over a window */
pData normalizeDataFromTo(pData T,int start,int end,Data max){
	int i = 0;
	if(T && max!=ZERO){
		for(i=start;i<end;i++)
			T[i] /= max;
	}
	return T;
}

/* finds a maximum data in a double-linked list */
Data findListMax(pListD L){
	Data max = ZERO;
	if(L){
		L->that = L->first;
		max = *((pData) L->first->item);
		while(L->that != NULL){
			if( max < *((pData) L->that->item)){
				max = *((pData) L->that->item);
			}
			L->that = L->that->next;
		}
	}
	return max;
}

/* calculates normalized values in the double-linked list */
/* TODO: what if values on the list are negative? */
pListD normalizeList(pListD L){
	if(L){
		if(L->first && L->first->next){
			Data max = findListMax(L);
			if(max != ZERO){
				L->that = L->first;
				while(L->that != NULL){
					Data value = *((pData) L->that->item);
					value = value / max;
					L->that = L->that->next;
				}
			}
			else max = NOTN;
		}
	}
	return L;
}



/* VARIANCE CALCULATIONS */

/* calc variance in a window in simple array of data */
Data varianceDataFromTo(pData T,int start,int end){
  Data ave = ZERO;
  Data sum = ZERO;
  Data var = NOTN;
	//printf("varianceDataFromTo(T,%i,%i)\n",start,end);
  ave = averageVectorFromTo(T,start,end);
  for(int i=start;i<end;i++){
		sum += (T[i]-ave) * (T[i]-ave);
		//printf("%f ",T[i]);
	}
	//printf("\n");
  var = sum / (end-start);
  return var;
}


/* calc variances from window over the vector */
pData varianceVectorWindow(pData T,int size,int wind){
  pData V = NULL;
  if(T && size>0 && wind>0 && wind<size){
    V = newData(size-wind);
    int start,end;
    for(int i=0;i<size-wind;i++){
      start = i;
      end = i+wind;
      V[i] = varianceDataFromTo(T,start,end);
    }
  }
  return V;
}


/* calc var for the whole set of data
 T = vector 1d
 n = number of elements */
Data varianceVector(pData T,int n){
  int i;
  Data ave = ZERO;
  Data sum = ZERO;
  Data var = NOTN;
  if(T!=NULL && n>0){
    ave = averageVector(T,n);
    for(i=0;i<n;i++) sum += (T[i] - ave) * (T[i] - ave);
    var = sum / n;
  }
  return var;
}

/* calc variance for the whole matrix with one simple hack */
Data varianceMatrix(pMatrix M){
	Data var = NOTN;
	if(M){
		var = varianceVector(M->T,M->W*M->H);	
	}
	return var;
}

/* calc variance in matrix subwindow with reverse mirroring behind boundaries */
/* x,y is the CENTER point, wh are size of the area AROUND */
/* so it is calculated over x-dx..x..x+dx,y-dy..y..y+dy area */
Data varianceSubMatrix(pMatrix M,int x,int y,int dx,int dy){
	int i,j,nx,ny;
	Data var = NOTN;
	// it is like filter but with constant area, so it is like in internal loop
	// idea: copy and make the matrix to calc from the original one
	printf("varianceSubMatrix:M,%i,%i, %i,%i\n",x,y,dx,dy);
	if(M){
		pMatrix N = newMatrix(dx*2+1,dy*2+1);
		printf("matrixN:\n");printMatrix(N);
		for(i=0;i<dx*2+1;i++){     // iteration over sub <--x-->
			for(j=0;j<dy*2+1;j++){   // iteration over sub y
				nx = x - dx + i;
				if(nx<0) nx = -nx - 1;
				if(nx>=M->W) nx = 2*M->W - nx;
				ny = y - dy + j;
				if(ny<0) ny = -ny - 1;
				if(ny>=M->H) ny = 2*M->H - ny;
				printf("N[%i,%i] = M[%i,%i], elem:%f\n",i,j,nx,ny,getElement(M,nx,ny));
				setElement(N,i,j, getElement(M,nx,ny));
			}
		}
		/*
		for(i=x-dx;x<=x+dx;i++)
			for(j=y-dy;j<=y+dy;j++){
				nx = x-dx+i
				for(fi=0;fi<N->W;fi++)
					for(fj=0;fj<N->H;fj++){
						nx = (i - N->W/2 + fi);
						ny = (j - N->H/2 + fj);
						nx = (nx<0)? -nx-1 : (nx>N->W-1)? M->W-(nx-M->W)-1 : nx;
						ny = (ny<0)? -ny-1 : (ny>N->H-1)? M->H-(ny-M->H)-1 : ny;
						nx = nx % M->W;
						ny = ny % M->H;
						printf("copy from M[%i,%i] to N[%i,%i]\n",nx,ny,fi,fj);
						setElement(N,fi,fj, getElement(M,nx,ny));
					}
			*/
		if(N){
			var = varianceMatrix(N);
			freeMatrix(N);
		}
	}
	return var;
}


/* calcs variance around single point, symmetrically, using reflection
 * so it means that for vector 1 2 3 4 5 6 7 and n=3 and wind=5 it will
 * calc for vector {3 2 1 [1 2 <3> 4 5 6 7] 7}, because wind is 5 to the
 * left and to the right from position n=3. The missing data will be mirrored
 * with reverse behind the boundaries */ 
Data varianceVectorAround1D(pVector V,int n,int wind){
	Data var = ZERO;
	//FIXME: VERY MEMORY INEFFECTIVE and INTENSIVE, but works
	if(V){
		pVector R = reverseVector(newCopyVector(V));
		pVector A = newFromVectors(R,V);
		pVector VV= newFromVectors(A,R);
		//printf("VV:");printVector(VV);printf("\n");
		var = varianceDataFromTo(VV->T, V->size+n-wind, V->size+n+wind+1);
		freeVector(VV);
		freeVector(A);
		freeVector(R);
	}
	return var;
}


/* non-standard operations, like randomize, etc. */

/* for seed init we are using µseconds */
long int getmicrosecond(){
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return tv.tv_usec;
}

pData randomizeData(pData T,int n){
	int i = 0;
	srand48(getmicrosecond());
  if(T == NULL) T = newData(n);
  for(i=0;i<n;i++) T[i] = drand48();
  return T;
}

pData generateData(pData T,int n,Data (*f)(int)){
	int i = 0;
	srand48(getmicrosecond());
  if(T==NULL) T = newData(n);
  for(i=0;i<n;i++) T[i] = (*f)(i);
  return T;
}

/* returns new data in the whole vector, randomized */
void randomizeVector(pVector V){
	if(V){
		V->T = randomizeData(V->T,V->size);
	}
}

/* reverses the whole vector using swapping elements, in-place change */
pVector reverseVector(pVector V){
	int i,half;
	Data tmp;
	if(V){
		half = V->size / 2;
		for(i=0; i<half; i++){
			tmp = V->T[i];
			V->T[i] = V->T[V->size-1-i];
			V->T[V->size-1-i] = tmp;
		}
	}
	return V;
}

/* randomize matrix with simple rand function */
void randomizeMatrix(pMatrix M) {
	if (M) {
		int i, j;
		for (i = 0; i < M->W; i++)
			for (j = 0; j < M->H; j++)
				setElement(M,i,j,(Data)rand() / (Data) MAXDATA);
	}
}

//FIXME - rewrite this to LINEAR
/* randomize matrix with simple rand function */
void drand48Matrix(pMatrix M) {
	if (M) {
		int i, j;
		for (i = 0; i < M->W; i++)
			for (j = 0; j < M->H; j++)
				setElement(M,i,j,(Data)drand48());
	}
}


/* make transpose matrix A to new matrix which is created and returned */
pMatrix transposeMatrix(pMatrix A){
	int i,j;
	pMatrix B = NULL;
	if(A){
		B = newMatrix(A->H,A->W); /* size is rotated 90° because of transposition */
		if(B)
			for(i=0;i<A->W;i++)
				for(j=0;j<A->H;j++)
					setElement(B,j,i,getElement(A,i,j));
/*					*(B->T+j*B->W+i) = *(A->T+i*A->W+j); */
	}
	return B;
}

/* multiplies matrix by a scalar value */
void mulMatrixBy(pMatrix A,Data scalar){
	int i,size = 0;
	if(A){
		size = A->W * A->H;
		for(i=0;i<size;i++) A->T[i] *= scalar;
	}
}
/* flips matrix horizontally and returns the new matrix */
void flipMatrixH(pMatrix A){
	int i,j;
	for(i=0; i<A->W; i++)
		for(j=0; j<A->H/2; j++)
			swapElement(A, i,j, i,A->H-j-1);
}

/* flips matrix verticall and returns the new matrix */
void flipMatrixV(pMatrix A){
	int i,j;
	for(i=0; i<A->W/2; i++)
		for(j=0; j<A->H; j++)
			swapElement(A, i,j, A->W-i-1,j);
}

/* sum the whole matrix */
Data reduceMatrix(pMatrix A){
	Data sum = ZERO;
	int i,size = 0;
	if(A)
		size = A->W * A->H;   // number of elements in the matrix
		for(i=0;i<size;i++)
			sum += *(A->T+i);   // linear sum (don't have to care about dimensions!)
	return sum;
}

/* makes filtering with the usage of matrix F over matrix M */
/* filtering is calculated as a simple sum of all corresponding cells */
/* result is a new filtered matrix */
pMatrix filterMatrix(pMatrix F, pMatrix M){
	int i,j,fi,fj,x,y;
	Data norm = reduceMatrix(F);
	pMatrix R = newMatrix(M->W,M->H);
	if(norm == ZERO) norm = (Data) 1.0;
	for(i=0;i<M->W;i++){
		for(j=0;j<M->H;j++){
			Data tmp = ZERO;
			for(fi=0;fi<F->W;fi++){
				for(fj=0;fj<F->H;fj++){
//					printf("i:%i, j:%i, fi:%i, fj:%i, i-FW/2+fi:%i,%%:%i j-FH/2+fj:%i,%%:%i ",i,j,fi,fj,i-F->W/2+fi,(i-F->W/2+fi)%M->W,j-F->H/2+fj,(j-F->H/2+fj)%M->H);
					x = (i - F->W/2 + fi);
					y = (j - F->H/2 + fj);
					if(x<0) x = -x - 1;
					if(y<0) y = -y - 1;
					if(x>F->W-1) x = M->W  - (x-M->W) -1;
					if(y>F->H-1) y = M->H  - (y-M->H) -1;
					x = x % M->W;
					y = y % M->H;
//					printf("x:%i, y:%i, M[i,j]:%f, F[x,y]:%f ",x,y,getElement(M,i,j),getElement(F,x,y));
//					*(R->T+i*R->W+j) = (*(M->T+i*M->W+j) * *(M->T+x*M->W+y)) / norm;
					tmp += getElement(M,x,y) * getElement(F,fi,fj);
					printf("tmp=%f\n",tmp);
				}
			}
			setElement(R, i, j,	tmp/norm );
		}
	}
	return R;
}

/* prepare gaussian distribution for a flitering, matrix is (radius*2+1)² */
pMatrix makeGaussian(int radius,Data sigma){
	int i,j;
	Data norm = ZERO;
	Data sisq = sigma * sigma;
	pMatrix G = NULL;
	if(sigma != ZERO){
		norm = 1/(2*3.1415926*sigma*sigma);
		G = newMatrix(radius*2+1,radius*2+1);
		for(i=-radius; i<=radius; i++)
			for(j=-radius; j<=radius; j++){
				Data v = norm * exp( -( pow((Data)i,2) + pow((Data)j,2) )/sisq );
				setElement(G,radius+i,radius+j, v);
			}
	}
	return G;
}

