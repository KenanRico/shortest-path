#include "_graph.h"

#include <stdlib.h>
#include <string.h>


/*
 *Construct from 1D array
 */
void CreateGraph(_Graph* graph, int const * mat, int N){
	graph->mat = malloc(sizeof(int*)*N);
	for(int i=0; i<N; ++i){
		graph->mat[i] = malloc(sizeof(int)*N);
		memcpy(graph->mat[i], &mat[i*N], N*sizeof(int));
	}
	graph->V = N;
	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j){
			graph->E += (graph->mat[i][j]==0) ? 0 : 1;
		}
	}
	graph->E /= 2;
}

/*
 *Construct from 2D array
 */
void CreateGraph2D(_Graph* graph, int const * const * mat, int N){
	graph->mat = malloc(sizeof(int*)*N);
	for(int i=0; i<N; ++i){
		graph->mat[i] = malloc(sizeof(int)*N);
		memcpy(graph->mat[i], mat[i], N*sizeof(int));
	}
	graph->V = N;
	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j){
			graph->E += (graph->mat[i][j]==0) ? 0 : 1;
		}
	}
	graph->E /= 2;
}


int GetNumberOfPaths(_Graph const * graph, int v){
	int num = 0;
	for(int i=0; i<graph->V; ++i){
		if(graph->mat[v][i]!=0){
			++num;
		}
	}
	return num;
}


void GetPathsAndWeights(_Graph const * graph, int v, int* dests, int* weights){
	int x = 0;
	for(int i=0; i<graph->V; ++i){
		if(graph->mat[v][i]!=0){
			dests[x] = i;
			weights[x] = graph->mat[v][i];
			++x;
		}
	}
}


void FreeGraph(_Graph* graph){
	for(int i=0; i<graph->V; ++i){
		free(graph->mat[i]);
	}
	free(graph->mat);
}
