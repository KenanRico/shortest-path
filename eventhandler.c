#include "eventhandler.h"
#include "SDL2headers.h"


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
	if(SDL_PollEvent(&eh->event)){
		switch(eh->event.type){
			case SDL_QUIT:
				eh->state = END;
				break;
			case SDL_MOUSEMOTION:
				eh->mouse_x = eh->event.motion.x;
				eh->mouse_y = eh->event.motion.y;
			case SDL_MOUSEBUTTONDOWN:
				if(eh->mouse_clicked || eh->mouse_held){
					eh->mouse_clicked = 0;
					eh->mouse_held = 1;
				}else{
					eh->mouse_clicked = 1;
				}
			case SDL_MOUSEBUTTONUP:
				eh->mouse_clicked = 0;
				eh->mouse_held = 0;
			default:
				break;
		}
	}
}

void eh_free(EventHandler* eh){

}
