
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

#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "data.h"
#include "stack.h"


/* newStackNode - creates a new node for stack structure, the empty one */
pStackNode newStackNode(){
	pStackNode s = (pStackNode) malloc(sizeof(StackNode));
	if(s){
		s->data = NULL;
		s->prev = NULL;
	}
	return s;
}
pStackNode defStackNode(pData data){
	pStackNode s = NULL;
	s = newStackNode();
	if(s) s->data = data;
	return s;
}
void freeStackNode(pStackNode s){
	if(s) free(s);
	s = NULL;
}

/* newStack: creates new empty stack and returns it as a pointer to newly created structure */
/* pStack S = newStack(); */
pStack newStack(){
  pStack S = (pStack) malloc(sizeof(Stack));
  S->stack = NULL;
  S->size = 0;
  return S;
}

/* freeStack: frees the whole stack, including all data inside */
/* freeStack(S); */   
/* [1] 2 3 4 : */
void freeStack(pStack S){
  if(S){
		if(S->stack){
			pStackNode v = S->stack;
			while(v->prev != NULL){
				S->stack = v->prev;
				freeStackNode(v);
			}
			freeStackNode(S->stack);
		}
    free(S);
    S=NULL;
  }
}

/* push: put the element to the stack. The newly added element is added on top of the stack, so next pop will get it. */
/* The same stack is returned, allowing chaining the command. */
/* push(S,element); */
/* or: */
/* S = push(push(push(S,element1),element2),element3); */
pStack push(pStack S,pData data){
//	printf("push: S:%p, data:%p %f\n",S,data,*((double*)data));
  if(!S){
		//printf("!S\n");
    S = newStack();
		if(S && S->stack == NULL){
			S->stack = defStackNode(data);
			if(S->stack){
				S->size = 1;
			}
		}
  }
  if(S != NULL){
//		printf("S!=NULL - true\n");
    pStackNode N = defStackNode(data);
    N->prev = S->stack;
    S->stack = N;
		S->size += 1;
  }
//	printf("push return: S:%p S->prev:%p, S->data:%p\n",S,S->prev,S->data);
  return S;
}

/* pop: removes the top element from the stack and returns it. The number of elements in the stack is decreased. If no elements */
/* was stored, returns NULL */
/* element = pop(S); */
pData pop(pStack S){
//	printf("pop: S:%p, &S:%p\n",*S,S);
  if(S){
    if(S->stack){
			//printf("  S exists, data exists\n");
      void *d  = S->stack->data;
      pStackNode p = S->stack->prev;
			//printf("  data: %p %f, prev: %p\n",(double*)d);
      freeStackNode(S->stack);
      S->stack = p;
			S->size -= 1;
			//printf("  S changed to: %p\n",S);
      return d;
    }
  }
  return NULL;
}

/* peek: returns the first element from the stack, and DO not removes it. This can be suboptimally implemented as pop with push. */
/* element = peek(S); */
/* */
pData peek(pStack S){
	return (S!=NULL && S->stack!=NULL) ? S->stack->data : NULL;
}

