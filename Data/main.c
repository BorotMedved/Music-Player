#include <time.h>
#include "textures.h"
#include "sound.h"
#include "window.h"
#include "common.h"

int main(){
	App a = {0};
	
	srand(time(NULL));
	initSDL(&a);
	
	const SDL_Rect b[11] = {
		{4,4,64,48}, // Back
		{204,4,64,48}, // Next
		{104,4,64,48}, // Play
		{4, 64, 256, 32}, // Pause
		{280, 64, 32,32},  // Time
		{280, 16, 26, 26}, // Shuffle
		{4, 460, 16, 16}, // <-
		{32, 460, 16, 16}, // <-
		{50,460,64,16}, // Song Count
		{300,460,16,16}, // +
		{280,460,16,16} // -
	};
	
	a.f = lF();
	SDL_Texture *t[10] = {0};
	
	Song s[255] = {0};
	a.dC = 18;
	oD(&a,t,s);
	pM(&a,s);
	
	w(&a,t,s);
	sV(&a, 64);
	
	while(1){
		
		ppS(&a);
		d(&a, t, b, s);
		dI(&a,b,s, t);
		psS(&a);
		SDL_Delay(16);
		if(Mix_PlayingMusic() == 0 && Mix_PausedMusic() != 1){
			n(&a,s);
		}
	}
	return 0;
}