
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

#ifndef __PIOTAO_LISTC_
#define __PIOTAO_LISTC_

#include "defs.h"

typedef struct ListC* pListC;

typedef struct ListC {
  Data data;
  pListC next;
} ListC;

pListC newListC();
pListC defListC(Data d);
pListC putListC(pListC L,Data d);
Data   popListC(pListC L);
pListC freeListC(pListC L);

#endif

