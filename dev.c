#include "builds.h"
#include "SDL2headers.h"
#include "renderenvironment.h"
#include "eventhandler.h"
#include "graph.h"
#include "states.h"
#include "system.h"

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
	
	while((states[RENDER]|states[EVENTS]|states[GRAPH])==0){
		eh_update(&events);
		re_update(&box);
		if(!graph.constructing){
			g_update(&graph, &events);
		}
		re_render(&box, &events, &graph);
	}

	re_free(&box);
	eh_free(&events);
	g_free(&graph);

	DestroySystem();
}
