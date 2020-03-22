#include "known.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>



void InitKnown(KnownVertices* known, int v, int s){
	known->set = malloc(sizeof(int)*v);
	known->set[0] = s;
	known->N = 1;
}

int Pop(KnownVertices* known, int const * distance){
	int min = 0x7fffffff; //0xffffffff/2 = 0x1111.........111/2 = 0x111........111>>1 = 0x01111......111 = 0x7ff..f
	int pop = 0;
	printf("known:\n");
	for(int i=0; i<known->N; ++i){
		printf("%d,%d ", known->set[i], distance[known->set[i]]);
		if(distance[known->set[i]]<min){
			min = distance[known->set[i]];
			pop = i;
		}
	}
	printf("\n");

	int ret = known->set[pop];
	memcpy(&known->set[pop], &known->set[pop+1], sizeof(int)*(known->N-pop-1));
	--known->N;

	printf("popping %d\n", ret);
	return ret;

}

/*optimize*/
void AddTo(KnownVertices* known, int dest){
	for(int i=0; i<known->N; ++i){
		if(known->set[i]==dest){
			return;
		}
	}

	printf("adding %d\n", dest);

	known->set[known->N] = dest;
	++known->N;
}

void FreeKnown(KnownVertices* known){
	free(known->set);
	known->set = NULL;
}

