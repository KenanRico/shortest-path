#ifndef _GRAPH_H
#define _GRAPH_H

typedef struct _Graph{
	int** mat;
	int V;
	int E;
} _Graph;

void CreateGraph(_Graph*, int const *, int);
void CreateGraph2D(_Graph*, int const * const *, int);
int GetNumberOfPaths(_Graph const *, int);
void GetPathsAndWeights(_Graph const *, int, int*, int*);
void FreeGraph(_Graph*);

#endif
