#include "path.h"
#include "states.h"
#include "graph.h"
#include "states.h"
#include "pair.h"

#include "algo/dijkstra.h"

#include <math.h>
#include <stdlib.h>


#define INCOMPLETE_END_PINTS 0x1



void p_init(Path* p, int n){
	p_reset(p);
	p->state = &states[PATH];
	p->jumps_cap = n;
	p->jumps = malloc(sizeof(Pair)*n);
	p->size = 0;
	p->render_size = 0;
}

void p_reset(Path* p){
	p->size = 0;
	p->dist = 0;
	p->src_v = -1;
	p->dest_v = -1;
	p->render_size = 0;
	phase=BUILD_MAP;
}

void p_select_endpoints(_Bool clicked, int x, int y, float const * px, float const * py, int size, Path* p){
	if(clicked){
		for(int i=0; i<size; ++i){
			double distance = sqrt(
				(x-px[i])*(x-px[i])+(y-py[i])*(y-py[i])
			);
			if (distance<vertex_radius){
				if(p->src_v==-1) p->src_v = i;
				else { p->dest_v = i; phase=FIND_SHORTEST_PATH; }
				break;
			}
		}
	}
}

void p_find_minimum(int const * const * graph, int size, Path* p){
	/*call dijkstra algo*/
	if(p->src_v!=-1 && p->dest_v!=-1){
		p->dist = Dijkstra2D(graph, size, p->src_v, p->dest_v);
		//^ Also get jumps in shortest path
		phase=BUILD_MAP;
	}else{
		*p->state = INCOMPLETE_END_PINTS;
	}
}

void p_free(Path* p){
	free(p->jumps);
}

void p_draw_path(Path* p){
	++p->render_size;
}
