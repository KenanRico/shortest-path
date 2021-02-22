#include "builds.h"
#include "SDL2headers.h"
#include "renderenvironment.h"
#include "eventhandler.h"
#include "graph.h"
#include "states.h"
#include "system.h"
#include "path.h"
#include "debug.h"

#include <stdio.h>
#include <unistd.h>
#include <time.h>


void DEV(){

	if(InitSystem()==0){
		exit(1);
	}

	RenderEnvironment box;
	re_init(&box);

	EventHandler events;
	eh_init(&events);

	Graph graph;
	g_init(&graph);
	
	Path path;
	p_init(&path, graph.size);
	
	struct timespec t0;
	while(states_healthy()){
		eh_update(&events);
		re_update(&box);
		re_clear(&box);
		re_render_statics(&box, &events, &graph, path.jumps, path.src_v, path.dest_v);
		switch(phase){
			case BUILD_MAP:
				g_update(&graph, &events);
				break;
			case SET_ENDPOINTS:
				p_select_endpoints(events.mouse_clicked, events.esc_pressed, events.mouse_x, events.mouse_y, graph.v_pos_x, graph.v_pos_y, graph.size, &path);
				break;
			case FIND_SHORTEST_PATH:
				p_find_minimum(graph.graph, graph.size, &path);
				printf("shortest is %d\n", path.dist);
				clock_gettime(CLOCK_REALTIME, &t0);
				break;
			case DRAW_PATH:
				if(path.jumps==NULL){
				    re_renderbadpath(&box, &graph, path.src_v, path.dest_v, &t0);
				}else{
				    re_rendergoodpath(&box, &graph, path.jumps, path.src_v, path.dest_v);
				}
				break;
			case RESET_PATH:
				p_reset(&path);
				break;
			default:
				break;
		}
		re_draw(&box);
	}

	printf("uh oh...\n\n");

	re_free(&box);
	eh_free(&events);
	g_free(&graph);

	DestroySystem();
}
