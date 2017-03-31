
/* [c] piotao Lib, 2010~, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 *
 * This module handles the most basic data definiotions and operations.
 * The data vector is just an bare array without size. Only a pointer to data.
 *
 * 20170306,pio: small repairs in calloc
 * 20170327,pio: refactoring and consolidation of piotaolib code
 */

#include <stdlib.h>   /* for malloc */
#include <string.h>   /* for memset */
#include <stdio.h>    /* for printf */
#include <stdarg.h>   /* for defData because of va_start etc. */

#include "data.h"     /* this module interface */
#include "listc.h"    /* for circular buffer list, used by defData */

pData newData(int n){
  pData p = (pData) calloc(n,sizeof(Data));
  memset(p,0,n);
  return p;
}

pData defData(Data d,...){
	va_list args;
	pData T = NULL;
	Data current = d;
	int i, n = 0;   /* number of elements passed */
	pListC L = newListC();

	va_start(args,d);
	for( ; current; current = va_arg(args,Data)){
		/*printf("infor: %f\n",current);*/
		L = putListC(L,current);
		n++;
	}
	va_end(args);
	T = newData(n);
	for(i=0;i<n;i++){
		Data d = popListC(L);
		printf("%i: %f\n",i,d);
		T[i] = d;
	}
	L=freeListC(L);
	return T;
}

void freeData(pData T){
  if(T) free(T);
  T=NULL;
}

void printData(pData T,int n){
	int i = 0;
  if(T){
    for(i=0;i<n;i++) printf("%f ",T[i]);
		printf("\n");
	}
  else
    printf("NULL");
}

