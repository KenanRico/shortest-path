#ifndef RENDER_UNIT_H
#define RENDER_UNIT_H

#include "SDL2headers.h"

typedef struct{
	SDL_Texture* texture;
	SDL_Rect srcrect;
	SDL_Rect destrect; 
} RenderUnit;

_Bool ru_init(RenderUnit*, SDL_Renderer*, const char*);
void ru_free(RenderUnit*);

#endif
