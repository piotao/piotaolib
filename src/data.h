
/* [c] piotao Lib, 2010~, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 *
 * This module handles the most basic data definiotions and operations.
 * The data vector is just an bare array without size. Only a pointer to data.
 */

#ifndef __PIOTAO_DATA__
#define __PIOTAO_DATA__

#include "defs.h"
 
pData newData(int n);
pData defData(Data d,...);
pData fromData(pData T,int n);
void freeData(pData T);
void printData(pData T,int n);

#endif

