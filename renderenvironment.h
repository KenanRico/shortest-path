#ifndef RENDER_ENVIRONMENT_H
#define RENDER_ENVIRONMENT_H

#include "SDL2headers.h"
#include "eventhandler.h"
#include "graph.h"

typedef struct Elements{
	SDL_Texture* vertex; SDL_Rect vertex_src; SDL_Rect vertex_dest; 
	SDL_Texture* edge; SDL_Rect edge_src; SDL_Rect edge_dest; 
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
void re_render(RenderEnvironment*, EventHandler const *, Graph const *);
void re_free(RenderEnvironment*);

#endif
