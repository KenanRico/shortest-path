#include "renderunit.h"
#include "SDL2headers.h"



_Bool ru_init(RenderUnit* ru, SDL_Renderer* renderer, const char* path){
	SDL_Surface* surf = IMG_Load(path);
	if(surf==NULL){
		return 0;
	}
	ru->texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	int w, h = 0;
	SDL_QueryTexture(ru->texture, NULL, NULL, &w, &h);
	ru->srcrect = (SDL_Rect){0,0,w,h};
	return 1;
}

void ru_free(RenderUnit* ru){
	SDL_DestroyTexture(ru->texture);
}
