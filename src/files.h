
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 * 20170328,pio: created
 */

#ifndef __PIOTAOLIB_FILES
#define __PIOTAOLIB_FILES

int fileExists(const char* name);
FILE* openFileToRead(const char* name);
FILE* openFileToWrite(const char* name);
FILE* openFileToAppend(const char* name);
void closeFile(FILE* f);


#endif
