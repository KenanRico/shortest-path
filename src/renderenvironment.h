#ifndef RENDER_ENVIRONMENT_H
#define RENDER_ENVIRONMENT_H

#include "SDL2headers.h"
#include "eventhandler.h"
#include "graph.h"
#include "renderunit.h"

typedef struct Elements{
	/*G=(V,E)*/
	RenderUnit vertex;
	RenderUnit edge;
	/*SP = shortest(G)*/
	RenderUnit sp_vertex;
	RenderUnit sp_edge;
} Elements;

typedef struct RenderEnvironment{
	SDL_Window* window;
	SDL_Renderer* renderer;
	Elements elements;
	uint32_t* state;
} RenderEnvironment;


extern int window_width;
extern int window_height;

void re_init(RenderEnvironment*);
void re_update(RenderEnvironment*);
void re_render(RenderEnvironment*, EventHandler const *, Graph const *, int const *, int, int);
void re_free(RenderEnvironment*);

#endif
