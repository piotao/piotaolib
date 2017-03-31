
#include <stdio.h>

#include "defs.h"
#include "data.h"
#include "listc.h"
#include "listd.h"

int main(){
	int i = 0;
	pListD L = NULL;
	pData T = defData(1.,2.,3.,4.,5.);
	printData(T,5);
	L = newListD();
	printf("printListD:\n");
	printListD(L);
	printf("printf:\n");
	printf("L:%p, L->size:%i, L->first:%p, L->last:%p, L->that:%p, L->that->next:%p, L->that->prev:%p\n",
		(void*)L,
		L->size,
		(pvoid)L->first,
		(pvoid)L->last,
		(pvoid)L->that,
		L->that!=NULL? (pvoid)L->that->next : NULL,
		L->that!=NULL? (pvoid)L->that->prev : NULL
	);

	printf("printListD:\n");
	for(i=0;i<5;i++){
		printf("%i:\n",i);
		insFirst(L,(pvoid)(T+i));
		/*insLast(L,(pvoid)(T+i)); */
		/*insBefore(L,(pvoid)(T+i));*/
		printListD(L);
	}
	
	freeListD(L);
	return 0;
}
