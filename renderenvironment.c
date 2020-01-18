#include "renderenvironment.h"



#define OK 0
#define BAD_WINDOW 0x1
#define BAD_RENDERER 0x2


void re_init(RenderEnvironment* re){
	/*set state*/
	re->state = OK;
	/*init window and renderer*/
	if((re->window = SDL_CreateWindow(
		"window 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 200, 500, SDL_WINDOW_RESIZABLE
	)) == NULL){
		re->state |= BAD_WINDOW;
		return;
	}
	if((re->renderer=SDL_CreateRenderer(re->window, -1, 0)) == NULL){
		re->state |= BAD_RENDERER;
		return;
	}
	SDL_SetRenderDrawColor(re->renderer, 240, 240, 240, 255);
}


void re_render(RenderEnvironment* re, EventHandler const * eh, Graph const * g){
	SDL_RenderClear(re->renderer);
	/*content*/

	SDL_RenderPresent(re->renderer);
}


void re_free(RenderEnvironment* re){
	SDL_DestroyWindow(re->window);
	SDL_DestroyRenderer(re->renderer);
}
