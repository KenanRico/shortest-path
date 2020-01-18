#ifndef RENDER_ENVIRONMENT_H
#define RENDER_ENVIRONMENT_H

#include "SDL2headers.h"
#include "eventhandler.h"
#include "graph.h"


typedef struct RenderEnvironment{
	SDL_Window* window;
	SDL_Renderer* renderer;
	uint32_t state;
} RenderEnvironment;

void re_init(RenderEnvironment*);
void re_render(RenderEnvironment*, EventHandler const *, Graph const *);
void re_free(RenderEnvironment*);

#endif
