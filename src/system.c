#include "system.h"
#include "SDL2headers.h"


_Bool InitSystem(){
	return (SDL_Init(SDL_INIT_EVERYTHING)==0 && TTF_Init()==0);
}

void DestroySystem(){
	TTF_Quit();
	SDL_Quit();
}
