#include "eventhandler.h"
#include "SDL2headers.h"
#include "states.h"

#include <stdio.h>


#define OK 0x0
#define END 0x1


void eh_init(EventHandler* eh){
	eh->mouse_x = 0.0f;
	eh->mouse_y = 0.0f;
	eh->mouse_clicked = 0;
	eh->mouse_held = 0;
	eh->state = &states[EVENTS];
	eh->enter_pressed = 0;
	eh->esc_pressed = 0;
}

void eh_update(EventHandler* eh){
	eh->mouse_clicked = 0;
	eh->enter_pressed = 0;
	eh->esc_pressed = 0;
	if(SDL_PollEvent(&eh->event)){
		switch(eh->event.type){
			case SDL_QUIT:
				*eh->state = END;
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
			case SDL_KEYDOWN:
				if(eh->event.key.keysym.sym==SDLK_RETURN){
					eh->enter_pressed = 1;
					printf("enter pressed\n");
				}else if(eh->event.key.keysym.sym==SDLK_ESCAPE){
					eh->esc_pressed = 1;
					printf("enter unpressed\n");
				}
				break;
			default:
				break;
		}
	}
}

void eh_free(EventHandler* eh){

}
