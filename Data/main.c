#include <time.h>
#include "textures.h"
#include "sound.h"
#include "window.h"
#include "common.h"

int main(){
	App a = {0};
	
	srand(time(NULL));
	initSDL(&a);
	
	const SDL_Rect b[6] = {
		{4,4,64,48},
		{204,4,64,48},
		{104,4,64,48},
		{4, 64, 256, 32},
		{280, 64, 32,32},
		{280, 16, 32, 32}
	};
	
	a.f = lF();
	SDL_Texture *t[5] = {0};
	
	Song s[255] = {0};
	oD(&a,t,s);
	pM(&a,s);
	
	wBT(&a,t);
	wBN(&a,s);
	
	while(1){
		cTM(&a,s);
		ppS(&a);
		d(&a, t, b);
		dI(&a,b,s, t);
		psS(&a);
		SDL_Delay(16);
		if(Mix_PlayingMusic() == 0 && Mix_PausedMusic() != 1){
			a.cS++;
			pM(&a,s);
			
			SDL_DestroyTexture(a.tN);
			wBN(&a,s);
		}
	}
	return 0;
}