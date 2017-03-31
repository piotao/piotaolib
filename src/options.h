
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 *
 * usage:
 * pConfig CONF = getOptions(argc,argv,
 *	newConfig(
 *		newItem('size','-size',tINT,newInt(16),
 *		newItem('runs','-runs',tINT,newInt(10),
 *		newItem('pi', NULL, pDouble,newDouble(3.14))))
 *	)
 * );
 *
 * 20100427, pio: created
 * 20170221, pio: included to the piotaolib library
 * 20170306, pio: ported to h&c style in split mode.
 */

#ifndef __PIOTAOLIB_OPTIONS
#define __PIOTAOLIB_OPTIONS

/* types stored in the configuration */
#define tINT    1
#define tFLOAT  2
#define tDOUBLE 3
#define tCHAR   4

/* internal types handled by configuration functions */
typedef int*    pInt;
typedef float*  pFloat;
typedef double* pDouble;
typedef char*   pChar;

typedef struct Item {  /* simple config element */
	char* name;          /* name of the config option */
	char* option;        /* name of the option from the command line, if any (can be NULL) */
	void* value;         /* value of the config option (can be any value) */
	int type;            /* type descriptor of the value */
	void* next;          /* next element link */
} Item;
typedef Item* pItem;

typedef struct Config {  /* configuration queue */
	int count;   					 /* number of elements */
	pItem items;           /* elements list */
} Config;
typedef Config* pConfig;

static pConfig CONF = NULL;  /* configuration singleton, can be set only by one invocation of newConfig */

#define MAKEBODY(TNAME,TYPE) TNAME data = (TNAME) malloc(sizeof(TYPE)); *data = value; return data
void* newInt(int value);
void* newFloat(float value);
void* newDouble(double value);
pChar newString(int len);
pChar copyString(const char* src);
pChar newChar(char* value);
pItem newItem(const char* name, const char* option, const int type, void* value, pItem next);
pConfig newConfig(pItem item);
pConfig addItem(pConfig C,pItem item);
void freeItems(pItem i);
void freeConfig(pConfig C);
pConfig getOptions(int argc,char* argv[],pConfig C);
int getConfAsInt(const char* key);
char* getConfAsStr(const char* key);

#endif /* OPTIONS_H_ */

