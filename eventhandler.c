#include "eventhandler.h"
#include "SDL2headers.h"

#include <stdio.h>


#define OK 0x0
#define END 0x1


void eh_init(EventHandler* eh){
	eh->mouse_x = 0.0f;
	eh->mouse_y = 0.0f;
	eh->mouse_clicked = 0;
	eh->mouse_held = 0;
	eh->state = OK;
}

void eh_update(EventHandler* eh){
	eh->mouse_clicked = 0;
	if(SDL_PollEvent(&eh->event)){
		switch(eh->event.type){
			case SDL_QUIT:
				eh->state = END;
				break;
			case SDL_MOUSEMOTION:
				eh->mouse_x = eh->event.motion.x;
				eh->mouse_y = eh->event.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				eh->mouse_clicked = 1;
				eh->mouse_held = 1;
				break;
			case SDL_MOUSEBUTTONUP:
				eh->mouse_held = 0;
				break;
			default:
				break;
		}
	}
}

void eh_free(EventHandler* eh){

}
