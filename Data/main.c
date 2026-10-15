#include "window.h"
#include "common.h"

int main(){
	
	Graphics g = {0};
	g.bI[8] = {
		{4,4,64,48}, // Back
		{204,4,64,48}, // Next
		{104,4,64,48}, // Play/Pause
		{280, 16, 26, 26}, // Shuffle
		{4, 460, 16, 16}, // <-
		{32, 460, 16, 16}, // ->
		{300,460,16,16}, // +
		{280,460,16,16} // -
	};
	g.bS[3] = {
		{4, 64, 256, 32}, // Name
		{280, 64, 32,32},  // Time
		{50,460,64,16} // Song Count
	};
	const SDL_Rect b[11] = {
		{4,4,64,48}, // Back
		{204,4,64,48}, // Next
		{104,4,64,48}, // Play/Pause
		{4, 64, 256, 32}, // Name
		{280, 64, 32,32},  // Time
		{280, 16, 26, 26}, // Shuffle
		{4, 460, 16, 16}, // <-
		{32, 460, 16, 16}, // ->
		{50,460,64,16}, // Song Count
		{300,460,16,16}, // +
		{280,460,16,16} // -
	};
	SDL_Texture *t[10] = {0};
	
	App a = {0};
	
	size_t sC = 255;
	Song *s = calloc(sC, sizeof *s);
	if (s == NULL) {
		perror("Failed to allocate songs");
		return 1;
	}
	
	initSDL(&a,t,s);
	
	while(1){
		r(&a,t,b,s);
	}
	return 0;
}