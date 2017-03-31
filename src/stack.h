
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 *
 * Stack implementation
 *
 * 20170224: created by piotao
 * 20170306: refactoring to split style
 * 20170318: changed comments, refactored code to WORK finally
 *
 * Stack: put something in it, take something from it.
 * Stack looks like this:
 *  Items: 4, Last item index: 3, First accessible: 3
 *  ----- 3 --> last inserted
 *  ----- 2
 *  ----- 1
 *  ----- 0 --> first inserted
 */

#ifndef __PIOTAO_STACK__
#define __PIOTAO_STACK__

#include "defs.h"
#include "data.h"

/* single node of stack element, keeps data and pointer to older element in chain */
typedef struct StackNode {
  pData data;
  struct StackNode* prev;
} StackNode;
typedef StackNode* pStackNode;

/* the general stack structure: keeps 'stack' pointer to the stack head. It is changing  during adding/removing elements */
typedef struct Stack {
	pStackNode stack;
	int size;
} Stack;
typedef Stack* pStack;

pStackNode newStackNode();
void freeStackNode(pStackNode s);
pStack newStack();
void freeStack(pStack S);
int countSize(pStack S);
pStack push(pStack S,pData data);
pData pop(pStack S);
pData peek(pStack S);

#endif

