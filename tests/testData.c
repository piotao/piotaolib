
#include <stdio.h>
#include "data.h"

#include "testing.h"

int main(){
	pData T = newData(3);
	OK("T is not null",T!=NULL);
	return 0;
}
