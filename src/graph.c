#include "graph.h"
#include "eventhandler.h"
#include "renderenvironment.h"
#include "states.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define OK 0x0
#define TOO_MANY_VERTICES 0x1

#define VERTEX_RELATIVE_RADIUS 0.04f

#define MINDIM(a,b) (((a)<(b))?(a):(b))


float vertex_radius = 0.00f;


void g_init(Graph* g){
	g->graph = malloc(MAX_VERTEX_COUNT*sizeof(int*));
	for(int i=0; i<MAX_VERTEX_COUNT; ++i){
		g->graph[i] = calloc(MAX_VERTEX_COUNT, sizeof(int));
	}
	memset(g->v_pos_x, 0, sizeof(int)*MAX_VERTEX_COUNT);
	memset(g->v_pos_y, 0, sizeof(int)*MAX_VERTEX_COUNT);
	g->size = 0;
	g->state = &states[GRAPH];
	g->first_v_in_edge = -1;
}

void g_update(Graph* g, EventHandler const * eh){

	vertex_radius = VERTEX_RELATIVE_RADIUS * MINDIM(window_width, window_height);

	if(eh->mouse_clicked){
		int vertex = g_select_vertex(eh->mouse_x, eh->mouse_y, g);
		if(vertex==-1){ /*no current vertex selected, add new*/
			if(g->size >= MAX_VERTEX_COUNT){
				*g->state |= TOO_MANY_VERTICES;
				return;
			}
			int i = g->size;
			++g->size;
			g->v_pos_x[i] = eh->mouse_x;
			g->v_pos_y[i] = eh->mouse_y;
		}else{ /*current vertex selected, start adding edge*/
			if(g->first_v_in_edge==-1){
				g->first_v_in_edge = vertex;
			}else{
				int dist = sqrt(
					(g->v_pos_x[g->first_v_in_edge]-g->v_pos_x[vertex])*(g->v_pos_x[g->first_v_in_edge]-g->v_pos_x[vertex])+
					(g->v_pos_y[g->first_v_in_edge]-g->v_pos_y[vertex])*(g->v_pos_y[g->first_v_in_edge]-g->v_pos_y[vertex])
				);
				g->graph[g->first_v_in_edge][vertex] = dist; //100 is placeholder edge weight
				g->graph[vertex][g->first_v_in_edge] = dist; //100 is placeholder edge weight
				g->first_v_in_edge = -1;
			}
		}
	}else if(eh->mouse_held){
		//?
	}

	if(eh->enter_pressed){
		phase = SET_ENDPOINTS;
	}
}

int g_select_vertex(int x, int y, Graph const * g){
	for(int i=0; i<g->size; ++i){
		double distance = sqrt(
			(x-g->v_pos_x[i])*(x-g->v_pos_x[i])+(y-g->v_pos_y[i])*(y-g->v_pos_y[i])
		);
		if (distance<vertex_radius){
			return i;
		}
	}
	return -1;
}

void g_free(Graph* g){
	for(int i=0; i<MAX_VERTEX_COUNT; ++i){
		free(g->graph[i]);
	}
	free(g->graph);
}
