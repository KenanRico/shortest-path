#include "debug.h"

#include <stdio.h>

void PrintIntArray(int const * arr, int size){
	for(int i=0; i<size; ++i){
		printf("%d ", arr[i]);
	}
	printf("\n");
}
