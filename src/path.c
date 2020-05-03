#include "path.h"
#include "states.h"
#include "graph.h"
#include "states.h"

#include "algo/dijkstra.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>


#define INCOMPLETE_END_PINTS 0x1



void p_init(Path* p, int n){
	p->state = &states[PATH];
	p->dist = 0;
	p->src_v = -1;
	p->dest_v = -1;
	p->size = 0;
	p->jumps = NULL;
	phase = BUILD_MAP;
}

void p_reset(Path* p){
	p->dist = 0;
	p->src_v = -1;
	p->dest_v = -1;
	p->size = 0;
	free(p->jumps);
	p->jumps = NULL;
	phase=BUILD_MAP;
}

void p_select_endpoints(_Bool clicked, _Bool esc, int x, int y, float const * px, float const * py, int size, Path* p){
	if(esc){
		p_reset(p);
		phase = BUILD_MAP;
	}else if(clicked){
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

#include <stdio.h>
void p_find_minimum(int const * const * graph, int size, Path* p){
	/*call dijkstra algo*/
	if(p->src_v!=-1 && p->dest_v!=-1){
		p->jumps = malloc(size*sizeof(int));
		memset(p->jumps, 0xff, size*sizeof(int));
		p->dist = Dijkstra2D(graph, size, p->src_v, p->dest_v, p->jumps, &p->size);
		if(p->dist==-1){
			free(p->jumps);
			p->jumps = NULL;
		}
		//^ Also get jumps in shortest path
		phase=MIN_PATH_FOUND;
	}else{
		*p->state = INCOMPLETE_END_PINTS;
	}
}

void p_free(Path* p){
	if(p->jumps!=NULL) free(p->jumps);
}
