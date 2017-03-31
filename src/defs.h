
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 *
 * This module handles the most basic data definitions and operations.
 * The "Data" type is an universal datatype used all across the whole piotaolib
 *
 * 20100423, pio: created the first version of this module
 * 20170221, pio: changes to the library, file included to piotaolib
 * 20170306, pio: applied to new style of libs (with *.h i *c)
 * 20170327, pio: consolidated into piotaolib library
 */

#ifndef DEFS_H_
#define DEFS_H_

#include <values.h>

/* this DEFINE selects the OVERALL GLOBAL DATATYPE in piotaolib library */
/* if you change this to integer types, some PRINT functions will behave strange */
#define SELECT_DOUBLE

typedef void* pvoid;
typedef pvoid* ppvoid;

/* universal determinators of any max value in any type */
#define MAX_OF(type) \
    (((type)(~0LLU) > (type)((1LLU<<((sizeof(type)<<3)-1))-1LLU)) ? (long long unsigned int)(type)(~0LLU) : (long long unsigned int)(type)((1LLU<<((sizeof(type)<<3)-1))-1LLU))
#define MIN_OF(type) \
    (((type)(1LLU<<((sizeof(type)<<3)-1)) < (type)1) ? (long long int)((~0LLU)-((1LLU<<((sizeof(type)<<3)-1))-1LLU)) : 0LL)

/* main data type in every library */

#if defined(SELECT_FLOAT)
#	define MAXDATA MAXFLOAT
	typedef float  Data;
#	define ZERO 0.000000000000000000000000000000000000000000000;
#	define NOTN MAX_OF(float);
#endif

#if defined(SELECT_DOUBLE) || defined(SELECT_LONGDOUBLE)
#	define MAXDATA MAXDOUBLE
# if defined(SELECT_DOUBLE)
		typedef double Data;
#		define ZERO (0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000)
#		define NOTN MAX_OF(double)
#	else
		typedef long double Data;
#		define ZERO (0.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000)
#		define NOTN MAX_OF(long double)
# endif
#endif

#if defined(SELECT_INT)
#	define MAXDATA MAXINT
	typedef signed int Data;
#	define ZERO 0l;
#endif

#if defined(SELECT_LONGINT)
#	define MAXDATA MAXLONG
	typedef signed long int Data;
#	define ZERO 0ll;
#endif

#ifndef MAXDATA
#	define MAXDATA 1e10
# define ZERO    0
#endif

typedef Data*  pData;
typedef pData* ppData;

#endif /* DEFS_H_ */

