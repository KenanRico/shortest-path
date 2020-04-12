#include "dijkstra.h"
#include "known.h"
#include "_graph.h"

#include <stdlib.h>
#include <string.h>



#define MIN(x,y) (((x)<(y))?(x):(y))


#include <stdio.h>


int DijCommonPath(_Graph* graph, int s, int t, int* jumps, int* size){
	int* distance = malloc(sizeof(int)*graph->V);
	for(int i=0; i<graph->V; ++i){
		distance[i] = -1;
	}
	distance[s] = 0;

	KnownVertices known;
	InitKnown(&known, graph->V, s);
	int curr = Pop(&known, distance);
	int* dest = malloc(sizeof(int)*graph->V);
	int* weight = malloc(sizeof(int)*graph->V);
	unsigned char* popped = calloc(graph->V, sizeof(unsigned char));
	/*optimize*/
	while(curr!=t){
		popped[curr] = 1;
		int degree = GetNumberOfPaths(graph, curr);
		GetPathsAndWeights(graph, curr, dest, weight);
		for(int i=0; i<degree; ++i){
			if(!popped[dest[i]]){
				AddTo(&known, dest[i]);
				if(distance[dest[i]]==-1){
					distance[dest[i]] = distance[curr] + weight[i];
					jumps[dest[i]] = curr;
				}else{
					//distance[dest[i]] = MIN(distance[dest[i]], distance[curr]+weight[i]); 
					if(distance[curr]+weight[i] < distance[dest[i]]){
						distance[dest[i]] = distance[curr]+weight[i];
						jumps[dest[i]] = curr;
					}
				}
			}
		}
		curr = Pop(&known, distance);
	}

	free(dest);
	free(weight);
	free(popped);

	FreeKnown(&known);
	FreeGraph(graph);

	int shortest = distance[curr];
	free(distance);

	return shortest;

}


int Dijkstra(int const * adj_mat, int n_nodes, int s, int t, int* jumps, int* size){
	_Graph graph = {NULL, 0, 0};
	CreateGraph(&graph, adj_mat, n_nodes);
	return DijCommonPath(&graph, s, t, jumps, size);
}


int Dijkstra2D(int const * const * adj_mat, int n_nodes, int s, int t, int* jumps, int* size){
	_Graph graph = {NULL, 0, 0};
	CreateGraph2D(&graph, adj_mat, n_nodes);
	return DijCommonPath(&graph, s, t, jumps, size);
}
