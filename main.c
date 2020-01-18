#include "builds.h"

#include <stdio.h>


#define DEBUG_DEV


int main(void){
#ifdef DEBUG_SBX
	SBX();
#endif
#ifdef DEBUG_DEV
	DEV();
#endif
#ifdef DEBUG_DEV
	PROD();
#endif
	return 0;
}

