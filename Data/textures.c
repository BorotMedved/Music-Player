#include "window.h"

void wBN(App *a, Song *s){
	SDL_Surface *t = TTF_RenderText_Solid(a->f,s[a->cS].n, (SDL_Color){255,255,255,255});
	a->tN = SDL_CreateTextureFromSurface(a->r, t);
	SDL_FreeSurface(t);
}

void wBT(App *a, SDL_Texture **t){
	const SDL_Color c = {255,255,255,255};
	SDL_Surface *bT[5] = {
		TTF_RenderText_Solid(a->f, "Back", c), 
		TTF_RenderText_Solid(a->f, "Next", c),
		TTF_RenderText_Solid(a->f, "Play", c),
		TTF_RenderText_Solid(a->f, "Pause", c),
		TTF_RenderText_Solid(a->f, "Shuffle", c)
	};
	t[0] = SDL_CreateTextureFromSurface(a->r, bT[0]);
	t[1] = SDL_CreateTextureFromSurface(a->r, bT[1]);
	t[2] = SDL_CreateTextureFromSurface(a->r, bT[2]);
	t[3] = SDL_CreateTextureFromSurface(a->r, bT[3]);
	t[4] = SDL_CreateTextureFromSurface(a->r, bT[4]);
	SDL_FreeSurface(bT[0]);
	SDL_FreeSurface(bT[1]);
	SDL_FreeSurface(bT[2]);
	SDL_FreeSurface(bT[3]);
	SDL_FreeSurface(bT[4]);
}

void cTM(App *a, Song *s)
{
    static int lastSeconds = -1;

    double t = Mix_GetMusicPosition(s[a->cS].m);
    int seconds = (int)t;

    if (seconds == lastSeconds) {
        return;
    }

    lastSeconds = seconds;

    char tT[16];

    u8 m = seconds / 60;
    u8 sc = seconds % 60;

    snprintf(tT, sizeof(tT), "%02d:%02d", m, sc);

    SDL_Surface *tS = TTF_RenderText_Solid(a->f,tT,(SDL_Color){255,255,255,255});

    if (tS == NULL) {
        return;
    }

    SDL_DestroyTexture(a->cT);

    a->cT = SDL_CreateTextureFromSurface(a->r, tS);

    SDL_FreeSurface(tS);
}

TTF_Font *lF(){
	
	TTF_Font *f = TTF_OpenFont("Songs/assets/PressStart2P-Regular.ttf", 8);

	if (f == NULL) {
		printf("Font failed: %s\n", TTF_GetError());
	}
	return f;
}

void dBT(App *a, SDL_Texture **t, const SDL_Rect *b){
	SDL_RenderCopy(a->r, t[0], NULL, &b[0]);
	SDL_RenderCopy(a->r, t[1], NULL, &b[1]);
	if(a->isP == true){
		SDL_RenderCopy(a->r, t[2], NULL, &b[2]);
	}
	else{
		SDL_RenderCopy(a->r, t[3], NULL, &b[2]);
	}
	SDL_RenderCopy(a->r, a->tN, NULL, &b[3]);
	SDL_RenderCopy(a->r, a->cT, NULL, &b[4]);
	SDL_RenderCopy(a->r, t[4], NULL, &b[5]);
	
}

void dB(App *a, const SDL_Rect *b){
	SDL_SetRenderDrawColor(a->r, 100, 100, 100, 255);
	SDL_RenderFillRect(a->r, &b[0]);
	SDL_RenderFillRect(a->r, &b[1]);
	SDL_RenderFillRect(a->r, &b[2]);
	SDL_SetRenderDrawColor(a->r, 200, 80, 80, 255);
	SDL_RenderFillRect(a->r, &b[5]);
}

void d(App *a, SDL_Texture **t, const SDL_Rect *b){
	dB(a,b);
	dBT(a,t,b);
}