
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 *
 * 20100422, by piotao, @hebron
 * 20170306: split style refactoring
 * 20170327,pio: added to piotaolib
 */

#include <stdlib.h>   /* for calloc */
#include <string.h>   /* for memset */
#include <stdio.h>    /* for printf */
#include <stdarg.h>   /* for defVector because of va_start macros etc */

#include "defs.h"     /* global typeset definitions like Data */
#include "data.h"     /* general data vector handlers */
#include "listc.h"    /* for ListC handling in defVector */
#include "vector.h"   /* handling of data vectors with size */

/* create new instance of vector data */
pVector newVector(int size){
	pVector V = (pVector) malloc(sizeof(Vector));
	memset(V,0,sizeof(Vector));
	V->T = newData(size);
	V->size = size;
	return V;
}

/* define new vector using variable number of arguments, as defData */
/* FIRST argument is the ENDING marker, it is not added to the list! */
/* and can't be specified inside data. Good values are big negatives numbers */
/* pVector V = defVector(-10000.0, 1.,2.,3,.4,.5,. -10000.0); */
pVector defVector(Data d, ...){
	pVector V = NULL;
	va_list args;
	pData T = NULL;
	Data current,ender = d;
	int i, n = 0;
	pListC L = newListC();
	va_start(args,d);
	while(current != ender){
		current = va_arg(args,Data);
		//printf("current=%f\n",current);
		if(current != ender){
			//printf("putted: %f\n",current);
			L = putListC(L,current);
			n++;
		}
	}
	/*
	for(;current; current = va_arg(args,Data)){
		printf("current:%f\n",current);
		L = putListC(L,current);
		n++;
	}
	*/
	va_end(args);
	T = newData(n);    /* this is the bare vector */
	V = newNoVector(n);/* this is initialized container of the vector */
	for(i=0; i<n; i++){
		T[i] = popListC(L);
		//printf("T[i]:%f\n",T[i]);
	}
	V->T = T;  /* finally, put bare vector into the container */
	L = freeListC(L);
	return V;
}

/* make new container, but don't initialize internal data buffer */
pVector newNoVector(int size){
	pVector V = (pVector) malloc(sizeof(Vector));
	/*memset(V,0,sizeof(Vector)); */
	V->T = NULL;
	V->size = size;
	return V;
}

/* puts existing data into a vector structure, this is NOT A COPY */
pVector newFromData(pData T,int SIZE){
	pVector V = newNoVector(SIZE);
	V->T = T;
	V->size = SIZE;
	return V;
}

/* copy specified amount of data and puts them into a vector */
pVector newCopyVector(pVector V){
	pVector N = NULL;
	int i;
	if(V){
		N = newVector(V->size);
		for(i=0; i<V->size; i++) N->T[i] = V->T[i];
	}
	return N;
}

/* copy specified parts of vector to another, NEW vector */
pVector newCopyVectorFromTo(pVector V,int start, int end){
	int i,size=0;
	pVector N = NULL;
	if(V){
		size = end - start;
		if(size < 0) size = -size;
		N = newVector(size+1);
		if(N) for(i=0; i<=size; i++) N->T[i] = V->T[start+i];
	}
	return N;
}

/* creates a joined COPY of two vectors */
pVector newFromVectors(pVector P,pVector Q){
	int i,j;
	pVector V = NULL;
	if(P && Q){
		V = newVector(P->size + Q->size);
		for(i=0; i<P->size; i++) V->T[i] = P->T[i];
		for(j=0; j<Q->size; j++) V->T[i+j] = Q->T[j];
	}
	return V;
}

/* swaps elements in the whole vector: namely reverse it! */
void swapElementV(pVector V, int a,int b,int c,int d){
	pData idx1,idx2;
	Data tmp;
	if(V){
		idx1 = V->T + a*V->size + b;
		idx2 = V->T + c*V->size + d;
		tmp = *idx1;
		*idx1 = *idx2;
		*idx2 = tmp;
	}
}

/* delete vector and remove its data from memory */
void freeVector(pVector V){
	if(V){
		freeData(V->T);
		free(V);
	}
}

/* free container only, but do not touch */
void freeNoVector(pVector V){
	if(V)	free(V);
}

/* prints the whole vector */
void printVector(pVector V){
	int i;
	if(V)
		for(i=0; i<V->size; i++)
			printf("%f ",V->T[i]);
	else
		printf("NULL");
}

/* just prints first count elements from vector */
void printVectorN(pVector V,int count){
	int i = 0;
	if(V){
		if(count<0){
			if(-count>V->size) count = -V->size;
			for(i=V->size+count;i<V->size;i++){
				printf("%.2f ",V->T[i]);
			}
		}
		else{
			if(count > V->size) count = V->size;
			for(i=0;i<count;i++){
				printf("%.2f ",V->T[i]);
			}
		}
	}
}

/* prints 'count' vector elements and newline */
void printlnVectorN(pVector V,int count){
	printVectorN(V,count);
	printf("\n");
}

/* prints all data using specified formatting */
void printVectorFmt(const char* format,pVector V){
	int i = 0;
	if(V){
		for(i=0;i<V->size;i++) printf(format,V->T[i]);
	}
	else{
		printf("NULL\n");
	}
}

