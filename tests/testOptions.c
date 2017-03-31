
#include <stdio.h>

#include "options.h"

int main(int argc, char** argv){

	pConfig conf = getOptions(argc,argv,
		newConfig(
			newItem("size","-size",tINT,newInt(16),
			newItem("runs","-runs",tINT,newInt(10),
			newItem("solo","-solo",tINT,newInt(20),
			newItem("text","-text",tCHAR,newString(20),NULL
		)))))
	);
	CONF = CONF;

	printf("options:\n");
	printf("SIZE: %i\n",getConfAsInt("size"));
	printf("RUNS: %i\n",getConfAsInt("runs"));
	printf("SOLO: %i\n",getConfAsInt("solo"));
	printf("TEXT: %s\n",getConfAsStr("text"));

	freeConfig(conf);

}
