#ifndef GRAPH_H
#define GRAPH_H

#include "eventhandler.h"

#include <stdint.h>

#define MAX_VERTEX_COUNT 1024


typedef struct Graph{
	int* graph;
	float v_pos_x[MAX_VERTEX_COUNT];
	float v_pos_y[MAX_VERTEX_COUNT];
	int size;
	_Bool constructing;
	uint32_t state;
} Graph;

void g_init(Graph*);
void g_update(Graph*, EventHandler const *);
void g_free(Graph*);

#endif
