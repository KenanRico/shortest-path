#include "path.h"
#include "states.h"
#include "graph.h"

#include "algo/dijkstra.h"

#include "math.h"



void p_init(Path* p){
	p_reset(p);
	p->state = &states[PATH];
}

void p_reset(Path* p){
	p->dist = 0;
	p->src_v = -1;
	p->dest_v = -1;
	p->endpoints_selected = 0;
}

void p_select_endpoints(_Bool clicked, int x, int y, float const * px, float const * py, int size, Path* p){
	if(clicked){
		for(int i=0; i<size; ++i){
			double distance = sqrt(
				(x-px[i])*(x-px[i])+(y-py[i])*(y-py[i])
			);
			if (distance<vertex_radius){
				if(p->src_v==-1) p->src_v = i;
				else { p->dest_v = i; p->endpoints_selected = 1; }
				break;
			}
		}
	}
}

void p_find_minimum(int const * const * graph, int size, Path* p){
	/*call dijkstra algo*/
	if(p->src_v!=-1 && p->dest_v!=-1){
		p->dist = Dijkstra2D(graph, size, p->src_v, p->dest_v);
	}
}
