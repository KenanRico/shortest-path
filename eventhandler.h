#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "SDL2headers.h"

#include <stdint.h>


typedef struct EventHandler{
	SDL_Event event;
	float mouse_x;
	float mouse_y;
	_Bool mouse_clicked;
	_Bool mouse_held;
	uint32_t state;
} EventHandler;

void eh_init(EventHandler*);
void eh_update(EventHandler*);
void eh_free(EventHandler*);

#endif
