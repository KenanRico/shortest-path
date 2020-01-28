#ifndef GRAPH_H
#define GRAPH_H

#include "eventhandler.h"

#include <stdint.h>

#define MAX_VERTEX_COUNT 1024


typedef struct Graph{
	int** graph;
	float v_pos_x[MAX_VERTEX_COUNT];
	float v_pos_y[MAX_VERTEX_COUNT];
	int size;
	int first_v_in_edge;
	_Bool constructing;
	uint32_t state;
} Graph;


extern float vertex_radius;


void g_init(Graph*);
void g_update(Graph*, EventHandler const *);
int g_select_vertex(int, int, Graph const *);
void g_free(Graph*);

#endif
