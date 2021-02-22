#ifndef RENDER_ENVIRONMENT_H
#define RENDER_ENVIRONMENT_H

#include "SDL2headers.h"
#include "eventhandler.h"
#include "graph.h"
#include "renderunit.h"

typedef struct{
	/*G=(V,E)*/
	RenderUnit vertex;
	RenderUnit edge;
	/*SP = shortest(G)*/
	RenderUnit sp_vertex;
	RenderUnit sp_edge;
	RenderUnit sp_bad_vertex;
} Elements;

typedef struct{
	SDL_Window* window;
	SDL_Renderer* renderer;
	Elements elements;
	uint32_t* state;
} RenderEnvironment;


extern int window_width;
extern int window_height;

void re_init(RenderEnvironment*);
void re_update(RenderEnvironment*);
void re_clear(RenderEnvironment*);
void re_render_statics(RenderEnvironment*, EventHandler const *, Graph const *, int const *, int, int);
void re_rendergoodpath(RenderEnvironment*, Graph const *, int const *, int, int);
void re_renderbadpath(RenderEnvironment*, Graph const *, int, int, struct timespec const *);
void re_draw(RenderEnvironment*);
void re_free(RenderEnvironment*);

#endif
