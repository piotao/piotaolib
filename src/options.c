
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor
 *
 * options.h, 2010-04-27, 20170306 split to h&c style, piotao
 * 20170221, pio: included to the piotaolib library
 * 20170306, pio: refactored, removed guard symbol
 * usage:
 * pConfig conf = getOptions(argc,argv,
 * 	newConfig(
 * 		newItem('size','-size',tINT,newInt(16),
 * 		newItem('runs','-runs',tINT,newInt(10),
 * 		newItem('pi', NULL, pDouble,newDouble(3.14))))
 * 	)
 * );
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "options.h"

void* newInt(int value){
	pInt data = (pInt) malloc(sizeof(int));
	*data = value;
	return (void*) data;
}

void* newFloat(float value){
	pFloat data = (pFloat) malloc(sizeof(float));
	*data = value;
	return (void*) data;
}

void* newDouble(double value){
	pDouble data = (pDouble) malloc(sizeof(double));
	*data = value;
	return (void*) data;
}

pChar newString(int len){
	pChar s = (pChar) malloc(len+1);
	memset(s,0,len+1);
	return s;
}

pChar copyString(const char* src){
	pChar dst = newString(strlen(src));
	strcpy(dst,src);
	return dst;
}
pChar newChar(char* value){
	return value;
}

pItem newItem(const char* name, const char* option, int type, void* value, pItem next){
	pItem I = (pItem) malloc(sizeof(Item));
	memset(I,0,sizeof(Item));
	I->name = copyString(name);
	I->option = copyString(option);
	I->type = type;
	I->value = value;
	I->next = next;
	return I;
}

/* create new configuration list */
pConfig newConfig(pItem item){
	pConfig C = NULL;
	pItem tmp = NULL;
	if(CONF) return CONF; /* return singleton */
	C = (pConfig) malloc(sizeof(Config));
	memset(C,0,sizeof(Config));
	if(item){
		C->items = item;
		tmp = item;
		while(tmp){
			C->count++;
			tmp = (pItem) tmp->next;
		}
	}
	CONF = C; /* make singleton */
	return C;
}

pConfig addItem(pConfig C,pItem item){
	pItem tmp = NULL;
	if(!C){
		C = newConfig(item);
		return C;
	}
	tmp = C->items;
	if(!tmp) C->items = item; /* it this was the first element */
	else{ /* or if we had elements before */
		while(!tmp->next) tmp = tmp->next; /* find the last element */
		tmp->next = item; /* add the new element at the end */
	}
	C->count++;
	return C;
}

void freeItems(pItem i){
	if(i){
		if(i->next) freeItems(i->next);
		free(i->value);
		free(i->name);
		free(i->option);
		free(i);
		i = NULL;
	}
}

void freeConfig(pConfig C){
	if(C){
		if(C->items) freeItems(C->items);
		free(C);
		C = NULL;
	}
}
/*
 * usage:
 * pConfig conf = getOptions(argc,argv,
 * 									newConfig(
 * 										newItem('size','-size',tINT,newInt(16),
 * 										newItem('runs','-runs',tINT,newInt(10),
 * 										newItem('pi', NULL, pDouble,newDouble(3.14))))
 * 									)
 * 								);
 */

/* analyze options list and define configuraion */
pConfig getOptions(int argc,char* argv[],pConfig C){
	int i,len = 0;
	if(C){
		for(i=1;i<argc;i++){
			pItem tmp = C->items; /* start with first stored configuration option */
			while(tmp){  					/* iterate over all configuration options */
				if(tmp->option){		/* if the option can be in command line (then it is not null here) */
					if(!strcmp(argv[i],tmp->option)){ /* if configuration name match */
						if(tmp->type == tINT){							/* ... then decide which type to store in ->value */
							tmp->value = (pInt) malloc(sizeof(int));
							*((pInt)tmp->value) = atoi(argv[i+1]);
							tmp->type = tINT;
							i++;
						}
						else if(tmp->type == tFLOAT){
							tmp->value = (pFloat) malloc(sizeof(float));
							*((pFloat)tmp->value) = (float) atof(argv[i+1]);
							tmp->type = tFLOAT;
							i++;
						}
						else if(tmp->type == tDOUBLE){
							tmp->value = (pDouble) malloc(sizeof(double));
							*((pDouble)tmp->value) = (double) atof(argv[i+1]);
							tmp->type = tDOUBLE;
							i++;
						}
						else if(tmp->type == tCHAR){
							len = strlen(argv[i+1]) + 1;
							tmp->value = (pChar) malloc(len);
							strcpy(tmp->value, argv[i+1]);
							tmp->type = tCHAR;
							printf("string: %s\n",(char*)tmp->value);
							i++;
						}
						else{
							printf("Option '%s' has no type defined, check your internal configuration settings.\n",tmp->option);
							break;
						} /* switch */
					}
					else{ /* option did not match, proceed with the loop */
					}
				}/* if(tmp->option) */
				else{/* this configuration option does not have command line parameter */
				}
				tmp = tmp->next;  /* advance to next configuration option */
			}
		}/* for loop */
	/* now we have all options parsed and data copied */
	}/* if(C) */
	return C;
}

int getConfAsInt(const char* key){
	if(CONF){
		pItem tmp = CONF->items;
		while(tmp){
			if(tmp->type == tINT){
				if(!strcmp(tmp->name,key)){
					return *((pInt)tmp->value);
				}
			}
			tmp = tmp->next;
		}
	}
	return -1;
}

char* getConfAsStr(const char* key){
	if(CONF){
		pItem tmp = CONF->items;
		while(tmp){
			printf("tmp:%p\n",(char*)tmp);
			if(tmp->type == tCHAR){
				if(!strcmp(tmp->name,key)){
					return (char*)tmp->value;
				}
			}
			tmp = tmp->next;
		}
	}
	return NULL;
}

