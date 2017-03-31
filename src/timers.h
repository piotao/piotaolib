
/* [c] piotao Lib, 20170327, @hebron <piotao@inf.ug.edu.pl>
 * The Piotao Lib, used to solve casual and common C-oriented programming
 * Licence: GPL 3.0, use at your own risk, no warranty at all, etc.
 * Compiler: gcc 5+, filesystem-based: Linux, Language: c with c++ flavor

 * 20100419,pio: created
 * 20170306,pio: refactoring
 * 20170327,pio: included to piotaolib
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#include <time.h>

#define TIMER_SCALE 1000000000

typedef struct timespec TimeSpec;
typedef TimeSpec* pTimeSpec;

/* simple timer for keeping time records in multiple instances */
typedef struct Timer {
	TimeSpec start; /* starting time */
	TimeSpec end;   /* stopping time */
	long int time;  /* period time (calculated during stop) */
} Timer;

/* pointer to Timer structure for passing by in functions */
typedef Timer* pTimer;

pTimer newTimer();
void freeTimer(pTimer pT);
void startTimer(pTimer pT);
void resetTimer(pTimer pT);
long int timespecDiff(pTimeSpec A, pTimeSpec B);
void stopTimer(pTimer pT);
double getTime(pTimer pT);
void printTimer(pTimer pT);
void printTimerFmt(char* fmt, pTimer pT);
char* formatTimer(char *fmt, pTimer pT);

#endif /* timers.h */

