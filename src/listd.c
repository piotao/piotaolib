
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 */

#include <stdio.h>     /* printf */
#include <stdlib.h>    /* malloc */
#include <string.h>    /* memset */

#include "listd.h"

/* defines new empty node - zeroed totally */
pNodeD newNodeD(){
	pNodeD n = (pNodeD) malloc(sizeof(NodeD));
	if(n){
		memset(n,0,sizeof(NodeD));
	}
	return n;
}

/* defines new empty node as a list element not bounded anywhere */
pNodeD defNodeD(pvoid item){
	pNodeD n = newNodeD();
	if(n){
		n->item = item;
		n->next = NULL;
		n->prev = NULL;
	}
	return n;
}

/* creates an empty double-linked list with 0 elements */
pListD newListD(){
	pListD L = (pListD) malloc(sizeof(ListD));
	if(L){
		L->size = 0;
		L->first = NULL;
		L->last = NULL;
		L->that = NULL;
	}
	return L;
}

/* creates a double-linked list with one, first element */
pListD defListD(pvoid item){
	pListD L = newListD();
	if(L){
		L->first = defNodeD(item);
		if(L->first){
			L->last = L->first;
			L->that = L->first;
			L->size = 1;
		}
	}
	return L;
}

/* adding to list at the very start, as a first element */
pListD insFirst(pListD L,pvoid item){
	if(!L) L = defListD(item);
	else{
		if(L->first == NULL){ /* empty list? no first? */
			L->first = L->last = L->that = defNodeD(item);
			L->size = (L->first != NULL) ? 1 : 0;
		}
		else{ /* there are some elements in the list already */
			pNodeD N = defNodeD(item);         /* •1--[2]--3• •4• */
			N->next = L->first;                /* •4-•1--[2]--3• */
			L->first->prev = N;
			L->first = N;                      /* •4--1--[2]--3• */
			L->size += 1;
		}
	}
	return L;
}

/* adding to the end of list */
pListD insLast(pListD L,pvoid item){
	if(!L){ L = defListD(item); }
	else{
		if(L->last == NULL){ /* empty list! */
			L->last = L->first = L->that = defNodeD(item);
			L->size = (L->last != NULL) ? 1 : 0;
		}
		else{ /* not empty list, there are some elements */
			pNodeD N = defNodeD(item);
			if(N){
				L->last->next = N;
				L->last->next->prev = L->last;
				L->last = N;
				L->size += 1;
			}
		}
	}
	return L;
}

/*FIXME/untested:  adding to the list at specified position, counting from first to n */
pListD insAt(pListD L,int n,pvoid item){
	if(!L) L = defListD(item);
	else{
		int i = 0;
		pNodeD l = L->first;
		while(i<L->size && l!=NULL && i!=n){
			l = l->next;
			i++;
		}
		L = insBefore(L,item);
	}
	return L;
}

/* FIXME/untested: adding to the list just somewhere in the middle, at current loc */
pListD insBefore(pListD L,pvoid item){
	if(!L) L = defListD(item);
	else{
		if(L->that == NULL){
			L->that = L->first = L->last = defNodeD(item);
			L->size = (L->that != NULL) ? 1 : 0;
		}
		else{
			pNodeD N = defNodeD(item);
			N->next = L->that;
			N->prev = L->that->prev;
			N->next->prev = N;
			N->prev->next = N;
			L->that = N;
		}
	}
	return L;
}

/* FIXME/untested: adding to the list just after the current element */
pListD insAfter(pListD L,pvoid item){
	if(!L) L = defListD(item);
	else{
		if(L->that == NULL){
			L->that = L->first = L->last = defNodeD(item);
			L->size = (L->that != NULL) ? 1 : 0;
		}
		else{
			pNodeD N = defNodeD(item);
			N->prev = L->that;
			N->next = L->that->next;
			N->prev->next = N;
			N->next->prev = N;
			L->that = N;
		}
	}
	return L;
}

/* moved internal list cursor to the start */
pListD toStart(pListD L){
	if(L) L->that = L->first;
	return L;
}

/* moved internal list cursor to the end */
pListD toEnd(pListD L){
	if(L) L->that = L->last;
	return L;
}

/* moves internal cursor one step to the end of the list */
pListD moveRight(pListD L){
	if(L && L->that && L->that->next)
		L->that = L->that->next;
	return L;
}

/* moves internal cursor one step to the start of the list */
pListD moveLeft(pListD L){
	if(L && L->that && L->that->prev)
		L->that = L->that->prev;
	return L;
}

/* removes the whole list and all it's internal data */
void freeListD(pListD L){
	if(L){
		if(L->size>0){
			while(L->last != NULL){
				pNodeD l = L->last;
				if(L->last->prev != NULL){
					L->last->prev->next = NULL;
				}
				else{
					L->first = NULL;
				}
				L->last = L->last->prev;
				L->that = L->last;
				free(l);
				L->size -= 1;
			}
		}
		free(L);
	}
}

/*FIXME/untested:  prints list: if n<0, then prints to the left, if n>0 prints to the right */
void printAt(pListD L,int n){

}

/* just prints the whole list */
void printListD(pListD L){
	if(L){
		pNodeD l = L->first;
		int i=0;
		while(l!=NULL){
			printf("%3i: ",L->size);

			if(l->prev == NULL) printf("<%9s","NULL");
			else printf("<%9p",(pvoid)l->prev);

			printf(" [%p:%f] ",(pvoid)l,*((pData)l->item));

			if(l->next == NULL) printf("%9s>","NULL");
			else printf("%9p>",(pvoid)l->next);

			if(l==L->first) printf(" first");
			if(l==L->that) printf(" that");
			if(l==L->last) printf(" last");
			printf("\n");

			l = l->next;
			i++;
		}
	}
	else{
		printf(": NULL\n");
	}
}


