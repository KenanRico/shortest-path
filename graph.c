#include "graph.h"
#include "eventhandler.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define OK 0x0
#define TOO_MANY_VERTICES 0x1


void g_init(Graph* g){
	g->graph = calloc(MAX_VERTEX_COUNT*MAX_VERTEX_COUNT, sizeof(int));
	memset(g->v_pos_x, 0, sizeof(int)*MAX_VERTEX_COUNT);
	memset(g->v_pos_y, 0, sizeof(int)*MAX_VERTEX_COUNT);
	g->size = 0;
	g->state = OK;
	g->constructing = 0;
}

void g_update(Graph* g, EventHandler const * eh){
	if(eh->mouse_clicked){
		if(g->size >= MAX_VERTEX_COUNT){
			g->state |= TOO_MANY_VERTICES;
			return;
		}
		int i = g->size;
		++g->size;
		g->v_pos_x[i] = eh->mouse_x;
		g->v_pos_y[i] = eh->mouse_y;
		printf("%f %f\n", g->v_pos_x[i], g->v_pos_y[i]);
	}else if(eh->mouse_held){
		//?
	}
}

void g_free(Graph* g){
	free(g->graph);
}
