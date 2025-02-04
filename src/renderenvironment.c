#include "renderenvironment.h"
#include "states.h"
#include "renderunit.h"

#include "SDL2headers.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>


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
	)) != NULL){
		SDL_MaximizeWindow(re->window);
	}else{
		*re->state |= BAD_WINDOW;
		return;
	}

	if((re->renderer=SDL_CreateRenderer(re->window, -1, 0)) == NULL){
		*re->state |= BAD_RENDERER;
		return;
	}
	SDL_SetRenderDrawColor(re->renderer, 230, 240, 240, 255);

	/*init render units*/
	ru_init(&re->elements.vertex, re->renderer, "../assets/vertex.png");
	ru_init(&re->elements.edge, re->renderer, "../assets/edge.png");
	ru_init(&re->elements.sp_vertex, re->renderer, "../assets/spvertex.png");
	ru_init(&re->elements.sp_edge, re->renderer, "../assets/spedge.png");
	ru_init(&re->elements.sp_bad_vertex, re->renderer, "../assets/spbadvertex.png");
	
}


void re_update(RenderEnvironment* re){
	SDL_GetWindowSize(re->window, &window_width, &window_height);
}

float slope(Graph const * g, int v1, int v2){
	return (float)(g->v_pos_y[v1]-g->v_pos_y[v2]) / (float)(g->v_pos_x[v1]-g->v_pos_x[v2]);
}

void SetWeightText(TTF_Font* font, SDL_Color color, SDL_Renderer* renderer, int weight, SDL_Texture** tex){
	char str[8];
	int len = 7;
	snprintf(str, len, "%d", weight);
	SDL_Surface* sm = TTF_RenderText_Solid(font, str, color);
	*tex = SDL_CreateTextureFromSurface(renderer, sm);
	SDL_FreeSurface(sm);
}
void SetWeightLocation(int x0, int y0, int x1, int y1, SDL_Rect* rect){
	rect->w = 50;
	rect->h = 20;
	rect->x = (x0+x1)/2-rect->w/2;
	rect->y = (y0+y1)/2-rect->h/2;
}
void RenderEdge(int _i, int _j, float const * pos_x, float const * pos_y, RenderUnit* edge, SDL_Renderer* renderer){
	int i = _i;
	int j = _j;
	if(pos_x[_i]>pos_x[_j]){
		i = _j;
		j = _i;
	}
	edge->destrect.w = sqrt(
		(pos_x[i]-pos_x[j])*(pos_x[i]-pos_x[j]) +
		(pos_y[i]-pos_y[j])*(pos_y[i]-pos_y[j])
	);
	edge->destrect.h = 100;
	edge->destrect.x = pos_x[i];
	edge->destrect.y = pos_y[i]-edge->destrect.h/2;
	/*rotate center*/
	SDL_Point center = (SDL_Point){0, edge->destrect.h/2};
	/*rotate angle; NOTE: flip the sign of dy to convert SDL coordinates to cartesian*/
	float angle = -atan((float)(pos_y[i]-pos_y[j])/(float)(pos_x[j]-pos_x[i]))*180.0f/3.1415926f;
	//float angle = counter;
	SDL_RenderCopyEx(renderer, edge->texture, &edge->srcrect, &edge->destrect, angle, &center, SDL_FLIP_NONE);
}
void RenderVertex(int i, float const * pos_x, float const * pos_y, RenderUnit* vertex, SDL_Renderer* renderer){
	vertex->destrect.w = vertex_radius*2;
	vertex->destrect.h = vertex_radius*2;
	vertex->destrect.x = pos_x[i]-vertex_radius;
	vertex->destrect.y = pos_y[i]-vertex_radius;
	SDL_RenderCopyEx(renderer, vertex->texture, &vertex->srcrect, &vertex->destrect, 0.0f, NULL, SDL_FLIP_NONE);
}

void re_clear(RenderEnvironment* re){
	SDL_RenderClear(re->renderer);
}

void re_render_statics(RenderEnvironment* re, EventHandler const * eh, Graph const * g, int const * jumps, int src_v, int dest_v){
	/* render egdes */
	for(int i=0; i<g->size; ++i){
		for(int j=0; j<g->size; ++j){
			if(g->graph[i][j] && g->v_pos_x[i]<g->v_pos_x[j]){
				RenderEdge(i, j, g->v_pos_x, g->v_pos_y, &re->elements.edge, re->renderer);
			}
		}
	}
	/* render vertices */
	for(int i=0; i<g->size; ++i){
		RenderVertex(i, g->v_pos_x, g->v_pos_y, &re->elements.vertex, re->renderer);
	}
	/*render weight values*/
	TTF_Font* font = TTF_OpenFont("../assets/Fonts/Mario-Kart-DS.ttf", 18); //need better management for this to avoid repeated allocation
	SDL_Color color = {150, 50, 50};
	for(int i=0; i<g->size; ++i){
		for(int j=0; j<g->size; ++j){
			if(g->graph[i][j]>0){
				SDL_Texture* weight_text = NULL;
				SetWeightText(font, color, re->renderer, g->graph[i][j], &weight_text);
				SDL_Rect rect;
				SetWeightLocation(g->v_pos_x[i], g->v_pos_y[i], g->v_pos_x[j], g->v_pos_y[j], &rect);
				SDL_RenderCopy(re->renderer, weight_text, NULL, &rect);
				SDL_DestroyTexture(weight_text);
			}
		}
	}
	TTF_CloseFont(font);
}


void re_rendergoodpath(RenderEnvironment* re, Graph const * g, int const * jumps, int src_v, int dest_v){
    static int* path = NULL;
    static int last = 0;
    static int curr = 0;
    if(path==NULL && last==0 && curr==0){
	path = malloc(g->size*sizeof(int));
	path[0] = dest_v;
	while(path[last]!=src_v){
	    path[last+1] = jumps[path[last]];
	    ++last;
	}
	curr = last;
    }else if(path!=NULL){
	if(curr==0){
	    curr = 0;
	    last = 0;
	    free(path);
	    path = NULL;
	    phase = RESET_PATH;
	}else{
	    RenderVertex(path[last], g->v_pos_x, g->v_pos_y, &re->elements.sp_vertex, re->renderer);
	    for(int j=last; j>=curr; --j){
		RenderEdge(path[j], path[j-1], g->v_pos_x, g->v_pos_y, &re->elements.sp_edge, re->renderer);
		RenderVertex(path[j-1], g->v_pos_x, g->v_pos_y, &re->elements.sp_vertex, re->renderer);
	    }
	    --curr;
	}
    }
}
void re_renderbadpath(RenderEnvironment* re, Graph const * g, int src_v, int dest_v, struct timespec const * t0){
    RenderVertex(src_v, g->v_pos_x, g->v_pos_y, &re->elements.sp_bad_vertex, re->renderer);
    RenderVertex(dest_v, g->v_pos_x, g->v_pos_y, &re->elements.sp_bad_vertex, re->renderer);
    struct timespec t1;
    clock_gettime(CLOCK_REALTIME, &t1);
    if((t1.tv_sec-t0->tv_sec)*1e9+(t1.tv_nsec-t0->tv_nsec) > 2e9){
	phase = RESET_PATH;
	return;
    }
}

void re_draw(RenderEnvironment* re){
	SDL_RenderPresent(re->renderer);
	if(phase==DRAW_PATH){
	    usleep(200000);
	}
}

void re_free(RenderEnvironment* re){
	SDL_DestroyWindow(re->window);
	SDL_DestroyRenderer(re->renderer);
	ru_free(&re->elements.vertex);
	ru_free(&re->elements.edge);
	ru_free(&re->elements.sp_vertex);
	ru_free(&re->elements.sp_edge);
}
