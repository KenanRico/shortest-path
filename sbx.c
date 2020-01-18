#include "builds.h"
#include "SDL2headers.h"

#include <stdio.h>

void SBX(){
	SDL_Window* window = SDL_CreateWindow(
		"window 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 200, 500, SDL_WINDOW_RESIZABLE
	);
	SDL_StartTextInput();
	SDL_Event event;
	while(1){
		if(SDL_PollEvent(&event)){

		}
	}
	printf("ok\n");
	getc(stdin);
	SDL_DestroyWindow(window);
}
