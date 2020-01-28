#include "renderenvironment.h"

#include "SDL2headers.h"


#define OK 0
#define BAD_WINDOW 0x1
#define BAD_RENDERER 0x2
#define BAD_IMAGE 0x4



int window_width = 400;
int window_height = 500;


void re_init(RenderEnvironment* re){
	/*set state*/
	re->state = OK;
	/*init window and renderer*/
	if((re->window = SDL_CreateWindow(
		"window 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_RESIZABLE
	)) == NULL){
		re->state |= BAD_WINDOW;
		return;
	}
	if((re->renderer=SDL_CreateRenderer(re->window, -1, 0)) == NULL){
		re->state |= BAD_RENDERER;
		return;
	}
	SDL_SetRenderDrawColor(re->renderer, 240, 240, 240, 255);

	/*load vertex texture*/
	SDL_Surface* surf = IMG_Load("assets/vertex.png");
	if(surf==NULL){
		re->state |= BAD_IMAGE;
		return;
	}
	re->elements.node = SDL_CreateTextureFromSurface(re->renderer, surf);
	SDL_FreeSurface(surf);
	{
		int w, h = 0;
		SDL_QueryTexture(re->elements.node, NULL, NULL, &w, &h);
		re->elements.vertex_src = (SDL_Rect){0,0,w,h};
	}
	/*load edge texture*/
	surf = IMG_Load("assets/edge.png");
	if(surf==NULL){
		re->state |= BAD_IMAGE;
		return;
	}
	re->elements.edge = SDL_CreateTextureFromSurface(re->renderer, surf);
	SDL_FreeSurface(surf);
	{
		int w, h = 0;
		SDL_QueryTexture(re->elements.edge, NULL, NULL, &w, &h);
		re->elements.edge_src = (SDL_Rect){0,0,w,h};
	}
}


void re_update(RenderEnvironment* re){
	SDL_GetWindowSize(re->window, &window_width, &window_height);
}


void re_render(RenderEnvironment* re, EventHandler const * eh, Graph const * g){

	SDL_RenderClear(re->renderer);
	for(int i=0; i<g->size; ++i){
		//SDL_RenderCopyEx(..);
	}
	SDL_RenderPresent(re->renderer);
}


void re_free(RenderEnvironment* re){
	SDL_DestroyWindow(re->window);
	SDL_DestroyRenderer(re->renderer);
	SDL_DestroyTexture(re->elements.node);
	SDL_DestroyTexture(re->elements.edge);
}
