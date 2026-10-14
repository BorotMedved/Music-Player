#include "window.h"

void wBN(App *a, Song *s){
	SDL_Surface *t = TTF_RenderUTF8_Solid(a->f,s[a->cS].dN, (SDL_Color){255,255,255,255});
	a->tN = SDL_CreateTextureFromSurface(a->r, t);
	SDL_FreeSurface(t);
}

void wSL(App *a, Song *s){
	u16 y = 80;
	for(u16 i = 0; i < a->sC;i++){
		if(y > 420){
			y = 80;
		}
		y += 20;
		s[i].b = (SDL_Rect){4, y, 312, 16};
		
		SDL_Surface *t = TTF_RenderUTF8_Solid(a->f,s[i].dN, (SDL_Color){255,255,255,255});
		s[i].t = SDL_CreateTextureFromSurface(a->r, t);
		SDL_FreeSurface(t);
	}
}

void wBT(App *a, SDL_Texture **t){
	const SDL_Color c = {255,255,255,255};
	char sC[32];
	snprintf(sC, sizeof(sC), "Songs: %u", (unsigned)a->sC);
	SDL_Surface *bT[10] = {
		TTF_RenderText_Solid(a->f, "Back", c), 
		TTF_RenderText_Solid(a->f, "Next", c),
		TTF_RenderText_Solid(a->f, "Play", c),
		TTF_RenderText_Solid(a->f, "Pause", c),
		TTF_RenderText_Solid(a->f, "Shuffle", c),
		TTF_RenderText_Solid(a->f, "<-", c),
		TTF_RenderText_Solid(a->f, "->", c),
		TTF_RenderText_Solid(a->f,sC, c),
		TTF_RenderText_Solid(a->f, "+", c),
		TTF_RenderText_Solid(a->f, "-", c)
	};
	
	for(u16 i = 0; i < 10 ; i++){
		t[i] = SDL_CreateTextureFromSurface(a->r, bT[i]);
		SDL_FreeSurface(bT[i]);
	}
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

void dSL(App *a, Song *s){
    u16 start = a->dC - 18;
    u16 end = a->dC;

    for (u16 i = start; i < end && i < a->sC; i++) {
        SDL_SetRenderDrawColor(a->r, 150, 10, 10, 255);
        SDL_RenderFillRect(a->r, &s[i].b);
        SDL_RenderCopy(a->r, s[i].t, NULL, &s[i].b);
    }
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
	for(u8 i = 5; i < 11;i++){
		SDL_RenderCopy(a->r, t[i-1], NULL, &b[i]);
	}
	
}

void dB(App *a, const SDL_Rect *b){
	SDL_SetRenderDrawColor(a->r, 100, 100, 100, 255);
	for(u8 i = 0; i < 3;i++){
		SDL_RenderFillRect(a->r, &b[i]);
	}
	SDL_SetRenderDrawColor(a->r, 200, 80, 80, 255);
	for(u8 i = 5; i < 8;i++){
		SDL_RenderFillRect(a->r, &b[i]);
	}
	SDL_SetRenderDrawColor(a->r, 150, 150, 150, 255);
	for(u8 i = 9; i < 11;i++){
		SDL_RenderFillRect(a->r, &b[i]);
	}
}

void d(App *a, SDL_Texture **t, const SDL_Rect *b, Song *s){
	cTM(a,s);
	dB(a,b);
	dSL(a,s);
	dBT(a,t,b);
}

void w(App *a, SDL_Texture **t, Song *s){
	wBN(a,s);
	wSL(a,s);
	wBT(a,t);
}

TTF_Font *lF(){
	
	TTF_Font *f = TTF_OpenFont("Assets/font.ttf", 8);

	if (f == NULL) {
		printf("Font failed: %s\n", TTF_GetError());
	}
	return f;
}