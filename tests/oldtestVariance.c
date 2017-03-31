
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "variance.h"
#include "listc.h"
#include "norm.h"

int SIZE = 50; // -s default data size
int WIND;      // -w window size (initialized as SIZE-5)
int DUMP = 0;  // -d debug, default=0
int EDIT = 0;  // if the values WERE entered by -e option
int FINP = 0;  // -f input was read from data file, if given

Data gen(int i){ return (i%2) ? 1 : 0; }
void printReport(int,int);
void readParams(int argc,char**argv,int* i,pData*T);
void readFile(int argc,char**argv,int* i,pData*T);

Data varianceFromToAndNormalize(pData T,int start,int end,Data max){
	if(max != ZERO)
		return varianceDataFromTo(T,start,end)/max;
	else
		return NOTN;
}

int main(int argc, char** argv){
  int i=0;
  pData T = NULL;
  WIND = SIZE-5;

  while(i<argc){
    if(!strcmp("-s",argv[i])) SIZE = atoi(argv[++i]);
    if(!strcmp("-w",argv[i])) WIND = atoi(argv[++i]);
    if(!strcmp("-d",argv[i])) DUMP = 1;
    if(!strcmp("-e",argv[i])){ // -e n1 n2 n3 n4... - just a number of values to initialize SIZE and vector
      readParams(argc,argv,&i,&T);
//      printData(T,SIZE);
    }
    if(!strcmp("-f",argv[i])){
      readFile(argc,argv,&i,&T);
      //printData(T,SIZE);
    }
    i++;
  }
  if(!EDIT && !FINP){ // we did not have any data, not entered by -e, not given by -f, so READ the STDIN.
		if(DUMP) fprintf(stderr,"reading from stdin...");
  }
  printReport(SIZE,WIND);

	T = normalizeData(T,SIZE,255);

  // here we SHOULD have ended or have some data to analyze

	// fill-in before data to move variance to the right coordinate
	for(i=0;i<WIND/2;i++) printf("%f\n",ZERO);
	if(WIND %2) printf("%f\n",ZERO); // correction for 1-pixel shift when odd window size

	// variance calculation
  for(i=0;i<SIZE-WIND+1;i++){
    printf("%f\n",varianceDataFromTo(T,i,i+WIND));
    //printf("%f\n",varianceFromToAndNormalize(T,i,i+WIND,2.0));
  }
	//fill-out after data to have full file
	for(i=SIZE-WIND/2;i<SIZE;i++) printf("%f\n",ZERO);
	if(WIND %2) printf("%f\n",ZERO); // correction for 1-pixel shift when odd window size

  return 0;
}

void printReport(int SIZE, int WIND){
  if(DUMP==1)
    printf("# SIZE: %i WIND: %i DUMP: %i EDIT: %i\n\n",SIZE,WIND,DUMP,EDIT);
}

void readParams(int argc,char**argv,int* i,pData*T){
  // reads and parse all params given as number after -e option, until either end of options or new option with '-'
  // is found. Numbers are added to data vector up to defined SIZE (default - 10 elements).
  // Best tactics: first set the size by -s 1000, then add few numbers with -e. The proper size is calculated too.
  (*T) = newData(SIZE);
  int n = 0;
  (*i)++;
  while(*i<argc && n<SIZE && argv[*i][0] != '-'){
    Data d = atof(argv[*i]);
    (*T)[n] = d;
    n++;
    (*i)++;
  }
  (*i)--; // tested - prevents to crash or ignoring last option in CLI
  SIZE = n;
  if(n>0) EDIT = 1;
}

// reads from file when name was specified in command line after -f option
void readFile(int argc,char**argv,int* i,pData*T){
  FILE* fin;
  (*i)++;
  if(*i<argc){ // if i is within range (below argc)

		//printf("file name: %s\n",argv[*i]);
    //deduce if we have to read from stdin or a regular file
    fin = (!strcmp(argv[*i],"-")) ? stdin : fopen(argv[*i],"r");

    if(!fin)
      perror("fopen"); // raise error if we can't open file to read

    else{
      // read file!
      pListC L = NULL; //newList(ZERO); // create buffer for data
      //TODO - first newlist can't be initialized with zero because it's not from data
      //TODO - change listc.c in a way that it is allowed to have NULL in cyclic list when
      //TODO - the list is empty, before adding any data to it, like here.
      int d = 0;
      int number = 0;
			int err;
      while( (err=fscanf(fin,"%i\n",&d)) != EOF ){ // read until EOF
//				printf("read:%i\n",d);
        if(L==NULL) L = defListC((Data)d);    // create when empty list - first add
        else L = putListC(L,d);               // store all data into a list
        number++;                            // increase a number of data read in already
      }
			//if(err){ perror("scanf"); printf("err:%i\n",err); }

      // now we have all data read into a buffer list, it's time to store it in a vector!
      SIZE = number;        // new data size - the number of read data, of course
      (*T) = newData(SIZE); // vector created, now fill it!
      for(int j=0;j<SIZE; (*T)[j++] = popListC(L) ); // nice unique for loop style
      fclose(fin);
      if(SIZE>0) FINP = 1;
      freeListC(L); // should be already empty - no need to double free!
    }
  }
}
