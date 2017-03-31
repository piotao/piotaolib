
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor

 * 20100419,pio: created
 * 20170306,pio: refactoring
 * 20170327,pio: included to piotaolib
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "timers.h"

/* create new, 0-filled timer structure */
pTimer newTimer() {
	pTimer pT = (pTimer) malloc(sizeof(Timer));
	memset(pT, 0, sizeof(Timer));
	return pT;
}

/* free timer memory */
void freeTimer(pTimer pT) {
	if (pT) free(pT);
}

/* launch timer by storing time in its starting register */
void startTimer(pTimer pT) {
	if (pT) clock_gettime(CLOCK_MONOTONIC, &(pT->start));
}

/* set any used timer to 0-state */
void resetTimer(pTimer pT) {
	if (pT) memset(pT, 0, sizeof(Timer));
}

/* calculate time difference between two given times */
long int timespecDiff(pTimeSpec A, pTimeSpec B) {
	return ((A->tv_sec * TIMER_SCALE) + A->tv_nsec) - ((B->tv_sec * TIMER_SCALE) + B->tv_nsec);
}

/* launch time measure by storing current time in ending register */
/* then calculate time period since start time and add to overall time */
void stopTimer(pTimer pT) {
	if (pT) {
		clock_gettime(CLOCK_MONOTONIC, &(pT->end));
		pT->time += timespecDiff(&(pT->end), &(pT->start));
	}
}

/* return real time as a double value */
double getTime(pTimer pT){
	if(pT){
		return (double) pT->time / (double) TIMER_SCALE;
	}
	else{
		return -1.0;
	}
}

/* print time in seconds, using scientific format */
void printTimer(pTimer pT) {
	if (pT) printf("%e", getTime(pT));
	else printf("NULL");
}

/* print time in seconds, using given format */
void printTimerFmt(char* fmt, pTimer pT) {
	if (pT) printf(fmt, getTime(pT));
	else printf("NULL");
}

char* formatTimer(char *fmt, pTimer pT){
	char* string = (char*) malloc(128);  /* due to this limitation, here can an overflow occur if buffer too small */
	if(pT){
		int len = 0;
		len = sprintf(string, fmt, getTime(pT));
		if(len <= 0) sprintf(string,"Error: %i chars returned from sprintf",len);
		return string;
	}
	else{
		strcpy(string,"NULL");
		return string;
	}
}


