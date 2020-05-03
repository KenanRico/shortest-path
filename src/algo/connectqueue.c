#include "connectqueue.h"

#include <stdlib.h>
#include <string.h>



void InitCQ(Queue* q, int size){
	q->capacity = size;
	q->size = 0;
	q->data = malloc(size*sizeof(int));
}

void AddToCQ(Queue* q, int v){
	q->data[q->size++] = v;
}

_Bool EmptyCQ(Queue* q){
	return q->size==0;
}

int PopCQ(Queue* q){
	if(q->size==0){
		return -1;
	}
	int popped = q->data[0];
	memcpy(&q->data[0], &q->data[1], sizeof(int)*(--q->size));
	return popped;
}

_Bool FoundInCQ(Queue* q, int v){
	for(int i=0; i<q->size; ++i){
		if(q->data[i]==v){
			return 1;
		}
	}
	return 0;
}

void FreeCQ(Queue* q){
	free(q->data);
}
