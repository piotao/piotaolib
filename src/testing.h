
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 *
 * testing.h - test module for all other modules
 *
 * 20170326,pio: created for tests
 * 20170327,pio: included to piotaolib
 */

#ifndef __PIO_TESTING_
#define __PIO_TESTING_

#include "defs.h"

void OK(const char* text,int result);
void notOK(const char* text,int result);
void isEQ(Data a,Data b);
void notEQ(Data a,Data b);

#endif
