
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 * 20170328,pio: created
 */


#include <unistd.h>
#include <stdio.h>

#include "files.h"

/* test if file exists, just like that, return: 0=no/error, 1=exists */
int fileExists(const char* name){
	return (access(name,F_OK) != -1) ? 1 : 0;
}

/* opens file to read */
FILE* openFileToRead(const char* name){
	FILE* file = fopen(name,"r");
	if(!file) fprintf(stderr,"Problem with file '%s' during opening to read.\n",name);
	return file;
}

/* opens file to write */
FILE* openFileToWrite(const char* name){
	FILE* file = fopen(name,"w");
	if(!file) fprintf(stderr,"Problem with file '%s' during opening to write.\n",name);
	return file;
}
	
/* opens file to append */
FILE* openFileToAppend(const char* name){
	FILE* file = fopen(name,"a");
	if(!file) fprintf(stderr,"Problem with file '%s' during opening to append.\n",name);
	return file;
}

/* closes file, if not closed */
void closeFile(FILE* f){
	if(f){
		fflush(f);
		fclose(f);
	}
}


