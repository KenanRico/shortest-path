#include "SDL2headers.h"

#include <stdio.h>

#define DEBUG_SBX

void SBX();


int main(void){
	SBX();
	return 0;
}

void SBX(){
#ifdef DEBUG_SBX
	SDL_Window* window = SDL_CreateWindow(
		"window 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 200, 800, SDL_WINDOW_RESIZABLE
	);
	printf("ok\n");
	getc(stdin);
	SDL_DestroyWindow(window);
#endif
}
