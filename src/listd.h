
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 * 
 * 20170306,pio: module created, @hebron, for 4piotaolib 
 * 20170318,pio: refactoring
 *
 * The list is constructed as follows:
 *       head
 *       ↓
 *       item     item    item
 * NULL <prev    <prev   <prev
 *       next>    next>   next>  NULL
 *
 * The 'this' pointer is a list cursor and can be moved left/right. List remembers
 * it's internal position and state. Adding next elements is possible at cursor,
 * after cursor, at the start and at the end. 
 *
 * The definition consists of ListNode double-linked element, and the ListContainer which
 * keeps all necessary data, like size, first and last pointers, cursor location, etc.
 *
 * Adding element to the list:
 *          1       2       3
 * NULL<--ITEM<-->THAT<-->ITEM-->NULL
 *          1      [2]     3
 *
 * insAfter(4):  1-2-3   ->   1-2-[4]-3
 * insBefore(4): 1-2-3   ->   1-[4]-2-3
 * insLast(4):   1-2-3   ->   1-2-3-[4]
 * insFirst(4):  1-2-3   ->   [4]-1-2-3
 *
 */

#ifndef __PIOTAO_DLIST_
#define __PIOTAO_DLIST_

#include "defs.h"

typedef struct NodeD* pNodeD;
typedef struct NodeD {
	pvoid  item;
	pNodeD next;
	pNodeD prev;
} NodeD;


typedef struct ListD* pListD;
typedef struct ListD {
	int size;
	pNodeD first;
	pNodeD last;
	pNodeD that;
} ListD;

pNodeD newNodeD();
pNodeD defNodeD(pvoid item);

pListD newListD();
pListD defListD(pvoid item);
void freeListD(pListD L);

pListD insFirst(pListD L,pvoid item);       /* before all others (first) */
pListD insLast(pListD L,pvoid item);        /* after all others (last) */
pListD insAt(pListD L,int n,pvoid item);    /*FIXME in arbitrary ordinary pos */
pListD insBefore(pListD L,pvoid item);      /*FIXME just before current */
pListD insAfter(pListD L,pvoid item);       /*FIXME just after current */

pListD toStart(pListD L);   /* moves internal cursor to the start */
pListD toEnd(pListD L);     /* moves internal cursor to the end */
pListD moveRight(pListD L); /* moves internal one item to right */
pListD moveLeft(pListD L);  /* moves internal to one item on the left */

void printAt(pListD L,int n); /* prints relative n elements */
void printListD(pListD L);    /* prints whole list */

#endif

