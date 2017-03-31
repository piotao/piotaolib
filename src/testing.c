
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

#include <stdio.h>
#include "testing.h"

/* prints OK with some  text if result is considered true */
void OK(const char* text,int result){
	if(result)
		printf("[OK] %s\n",text);
	else
		printf("[--] %s\n",text);
}

/* prints OK with some  text if result is considered not true */
void notOK(const char* text,int result){
	if(!result)
		printf("[OK] %s\n",text);
	else
		printf("[--] %s\n",text);
}


/* prints OK if both data are equal */
void isEQ(Data a,Data b){
	if(a == b) printf("[OK] a[%f]==b[%f]\n",a,b);
	else       printf("[--] a[%f]==b[%f]\n",a,b);

}

/* prints OK if both data are not equal */
void notEQ(Data a,Data b){
	if(a != b) printf("[OK] a[%f]!=b[%f]\n",a,b);
	else       printf("[--] a[%f]!=b[%f]\n",a,b);
}

