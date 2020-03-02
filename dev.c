#include "builds.h"
#include "SDL2headers.h"
#include "renderenvironment.h"
#include "eventhandler.h"
#include "graph.h"
#include "states.h"
#include "system.h"
#include "path.h"

#include <stdio.h>


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
	p_init(&path);
	
	while(states_healthy()){
		eh_update(&events);
		re_update(&box);
		switch(phase){
			case BUILD_MAP:
				g_update(&graph, &events);
				break;
			case SET_ENDPOINTS:
				p_select_endpoints(events.mouse_clicked, events.mouse_x, events.mouse_y, graph.v_pos_x, graph.v_pos_y, graph.size, &path);
				break;
			case FIND_SHORTEST_PATH:
				p_find_minimum(graph.graph, graph.size, &path);
				printf("shortest is %d\n", path.dist);
				p_reset(&path);
				phase = BUILD_MAP; //put this in func
			case ANIMATE_PATH:
			default:
				break;
		}
		re_render(&box, &events, &graph);
	}

	re_free(&box);
	eh_free(&events);
	g_free(&graph);

	DestroySystem();
}
