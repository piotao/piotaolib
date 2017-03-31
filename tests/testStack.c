
#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "data.h"
#include "stack.h"

int main(){
	pStack S = NULL;
	double*d1,*d2,*d3;
	d1 = (double*)malloc(sizeof(double));*d1=1.0;
	d2 = (double*)malloc(sizeof(double));*d2=2.0;
	d3 = (double*)malloc(sizeof(double));*d3=3.0;
	S = newStack();
	S=push(S,(pvoid)d1);
	printf("a:%p\n",(pvoid)S);
	printf("b:%p\n",(pvoid)S->stack);
	if(S->stack){
		printf("c:%p\n",(pvoid)S->stack->data);
		printf("1:%f\n",*((double*)S->stack->data));
	}
	S=push(S,(pvoid)d2);
	printf("2:%f\n",*((double*)S->stack->prev->data));
	S=push(S,(pvoid)d3);
	printf("3:%f\n",*((double*)S->stack->prev->prev->data));
	printf("size: %i\n",S->size);
	printf("S:%p has stack: %p, got: %f\n",(pvoid)S,(pvoid)S->stack,*((pData)pop(S)));
	printf("S:%p has stack: %p, got: %f\n",(pvoid)S,(pvoid)S->stack,*((pData)pop(S)));
	printf("S:%p has stack: %p, got: %f\n",(pvoid)S,(pvoid)S->stack,*((pData)pop(S)));
	freeStack(S);
	freeData(d1);
	freeData(d2); 
	freeData(d3);
	return 0;
}
