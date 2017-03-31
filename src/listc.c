
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 *
 * Cyclic List implemenetation suitable for quick adding and fetching atomic data
 * without limits. It can be used to read any data from file, and after reading,
 * storing them in arrays, only when the total size is known.
 *
 * Structure:
 *					 ↓HEAD
 *	 [4]--->[5]--->[1]--->[2]--->[3]
 *		↑														|
 *		+---------------------------+
 * So, the first element added is just pointing to itself. After second is added,
 * the second is the last one, and it points with next to the the first one. If third
 * is added, it is kept as current list head, pointint again to the first added.
 * This organization allow for O(1) adding and O(1) getting the items, while FIFO order
 * is maintained! No need to rewind the list in any direction, it just grows, etc.
 * Fragile moments: adding first two elements, removing last two elements.
 * Cyclic can be dangerous with removing with loops.
 * PROS:
 *	 1. Low memory footprint (only 4*N bytes more)
 *	 2. O(1) insert and retrieve
 * CONS:
 *	 1. Number of elements is unknown, has to be calculated in O(n)
 *	 2. Cyclic dependence with pointers - a bit dangerous
 * Usage:
 * pListC L = newListC();
 * pListC L = defListC(otherList);
 * L = putListC(L,data);
 * data = popListC(L);
 * freeListC(B);
 */

#include <stdlib.h>

#include "defs.h"
#include "listc.h"

/* creates a bare empty list, no data inside, no loop in pointers */
pListC newListC(){
	pListC L = (pListC) malloc(sizeof(ListC));
	if(L){
		L->data = ZERO;
		L->next = NULL;
	}
	return L;
}

/* creates new list and the first data node, pointing to itself. */
pListC defListC(Data d){
	pListC L = newListC();
	if(L){
		L->data = d; /* store data */
		L->next = L; /* make circular */
	}
	return L;
}

/* stores new data in the list, keeping their circular structure at LAST before head */
pListC putListC(pListC L,Data d){
	if(L==NULL) L = defListC(d);  /* create new 1-element list */
	else{ /* if list already exists */
		if(L->next == NULL){ /* list was empty, so we are adding first element */
			L->next = L;
			L->data = d;
		}
		else{
			if(L->next == L){ /* there is only one element already */
				/*add new one */
				pListC N = defListC(d);	/* new circular node */
				N->next = L;
				L->next = N;
				L = N;
			}
			else{ /* there are more elements, ok, next is 1st, current is last so is head */
				pListC N	 = defListC(d); /* add new circular data */
				N->next = L->next;
				L->next = N;
				L = N;
			}
		}
	}
	return L;
}

/* fetches one element from the list, removing it from the list */
Data popListC(pListC L){
	Data d = NOTN;
	pListC tmp = NULL;
	if(L){
		if(L->next == NULL){	/*try to pop data from empty list */
			d = ZERO;
		}
		else if(L != L->next){ /* some normal value */
			d = L->next->data;
			tmp = L->next->next;
			free(L->next);
			L->next = tmp;
		}
		else{ /* now L=L->next, so we have the last element */
			d = L->data;
			L->next = NULL;
			L->data = ZERO;
		}
	}
	return d;
}

/* removes the entire list */
pListC freeListC(pListC L){
	if(L==NULL){
		return NULL;
	}
	else{ /* we have elements */
		while(L->next != NULL && L->next != L){
			pListC tmp = L->next->next;
			L->next->data = ZERO;
			L->next->next = NULL;
			free(L->next);
			L->next = tmp;
		}
		if(L->next != NULL && L->next == L){ /* the last element */
			L->data = ZERO;
			L->next = NULL;
			free(L);
			L = NULL;
		}
		if(L->next == NULL){ /* probably empty list */
			L->data = ZERO;
			free(L);
			L = NULL;
		}
	}
	return L;
}

