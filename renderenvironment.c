#include "renderenvironment.h"
#include "states.h"

#include "SDL2headers.h"

#include <stdlib.h>


#define OK 0
#define BAD_WINDOW 0x1
#define BAD_RENDERER 0x2
#define BAD_IMAGE 0x4

#define _MIN(x,y) (x)<(y)?(x):(y)


int window_width = 400;
int window_height = 500;


void re_init(RenderEnvironment* re){
	/*set state*/
	re->state = &states[RENDER];
	/*init window and renderer*/
	if((re->window = SDL_CreateWindow(
		"window 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_RESIZABLE
	)) == NULL){
		*re->state |= BAD_WINDOW;
		return;
	}
	if((re->renderer=SDL_CreateRenderer(re->window, -1, 0)) == NULL){
		*re->state |= BAD_RENDERER;
		return;
	}
	SDL_SetRenderDrawColor(re->renderer, 240, 240, 240, 255);

	/*load vertex texture*/
	SDL_Surface* surf = IMG_Load("assets/vertex.png");
	if(surf==NULL){
		*re->state |= BAD_IMAGE;
		return;
	}
	re->elements.vertex = SDL_CreateTextureFromSurface(re->renderer, surf);
	SDL_FreeSurface(surf);
	{
		int w, h = 0;
		SDL_QueryTexture(re->elements.vertex, NULL, NULL, &w, &h);
		re->elements.vertex_src = (SDL_Rect){0,0,w,h};
	}
	/*load edge texture*/
	surf = IMG_Load("assets/edge.png");
	if(surf==NULL){
		*re->state |= BAD_IMAGE;
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

float slope(Graph const * g, int v1, int v2){
	return (float)(g->v_pos_y[v1]-g->v_pos_y[v2]) / (float)(g->v_pos_x[v1]-g->v_pos_x[v2]);
}

void re_render(RenderEnvironment* re, EventHandler const * eh, Graph const * g){

	SDL_RenderClear(re->renderer);
	for(int i=0; i<g->size; ++i){
		re->elements.vertex_dest.w = vertex_radius*2;
		re->elements.vertex_dest.h = vertex_radius*2;
		re->elements.vertex_dest.x = g->v_pos_x[i]-vertex_radius;
		re->elements.vertex_dest.y = g->v_pos_y[i]-vertex_radius;
		SDL_RenderCopyEx(re->renderer, re->elements.vertex, &re->elements.vertex_src, &re->elements.vertex_dest, 0.0f, NULL, SDL_FLIP_NONE);
		for(int j=0; j<g->size; ++j){
			/*edge render placeholder*/
			if(g->graph[i][j]){
				re->elements.edge_dest.x = _MIN(g->v_pos_x[i], g->v_pos_x[j]);
				re->elements.edge_dest.y = _MIN(g->v_pos_y[i], g->v_pos_y[j]);
				re->elements.edge_dest.w = abs(g->v_pos_x[i]-g->v_pos_x[j]);
				re->elements.edge_dest.h = abs(g->v_pos_y[i]-g->v_pos_y[j]);
				SDL_RendererFlip flip = (slope(g,i,j)<0) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
				SDL_RenderCopyEx(re->renderer, re->elements.edge, &re->elements.edge_src, &re->elements.edge_dest, 0.0f, NULL, flip);
			}
		}
	}
	SDL_RenderPresent(re->renderer);
}


void re_free(RenderEnvironment* re){
	SDL_DestroyWindow(re->window);
	SDL_DestroyRenderer(re->renderer);
	SDL_DestroyTexture(re->elements.vertex);
	SDL_DestroyTexture(re->elements.edge);
}
