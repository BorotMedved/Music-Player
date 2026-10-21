#include "window.h"

void cSL(u8 sC, Song *s){
    for (u16 i = 0; i < sC; i++) {
		SDL_DestroyTexture(s[i].t);
		s[i].t = NULL;
    }
}

void wBN(App *a, Song *s){
    SDL_Surface *su = TTF_RenderUTF8_Solid(a->f, s[a->cS].dN,(SDL_Color){255, 255, 255, 255});

    if (su == NULL) {
        return;
    }

    SDL_Texture *t = SDL_CreateTextureFromSurface(a->r, su);
    SDL_FreeSurface(su);

    if (t != NULL) {
        if (a->tN != NULL) {
            SDL_DestroyTexture(a->tN);
        }

        a->tN = t;
    }
}

void wSL(App *a, Song *s){
	u16 y = 80;
	u16 start = a->dC - 18;
    u16 end = a->dC;

    for (u16 i = start; i < end && i < a->sC; i++) {
        if(y > 420){
			y = 80;
		}
		y += 20;
		s[i].b = (SDL_Rect){4, y, 312, 16};
		
		if (s[i].t != NULL) {
			SDL_DestroyTexture(s[i].t);
			s[i].t = NULL;
		}
		
		SDL_Surface *t = TTF_RenderUTF8_Solid(a->f,s[i].dN, (SDL_Color){255,255,255,255});
		s[i].t = SDL_CreateTextureFromSurface(a->r, t);
		SDL_FreeSurface(t);
    }
}

void wBT(App *a, SDL_Texture **t){
	const SDL_Color c = {255,255,255,255};
	char sC[32];
	snprintf(sC, sizeof(sC), "Songs: %u", (unsigned)a->sC);
	SDL_Surface *bT[11] = {
		TTF_RenderText_Solid(a->f, "Back", c), 
		TTF_RenderText_Solid(a->f, "Next", c),
		TTF_RenderText_Solid(a->f, "Play", c),
		TTF_RenderText_Solid(a->f, "Pause", c),
		TTF_RenderText_Solid(a->f, "Shuffle", c),
		TTF_RenderText_Solid(a->f, "<-", c),
		TTF_RenderText_Solid(a->f, "->", c),
		TTF_RenderText_Solid(a->f, "+", c),
		TTF_RenderText_Solid(a->f, "-", c),
		TTF_RenderText_Solid(a->f,"~", c),
		TTF_RenderText_Solid(a->f,sC, c)
	};
	
	for(u16 i = 0; i < 11; i++){
		t[i] = SDL_CreateTextureFromSurface(a->r, bT[i]);
		SDL_FreeSurface(bT[i]);
	}
}

void cTM(App *a, Song *s){
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

void dBT(App *a, Graphics *g){
	SDL_RenderCopy(a->r, a->tN, NULL, &g->bS[0]);
	SDL_RenderCopy(a->r, a->cT, NULL, &g->bS[1]);
	SDL_RenderCopy(a->r, g->t[10], NULL, &g->bS[2]);
	
	if(a->isP == true){
		SDL_RenderCopy(a->r, g->t[2], NULL, &g->bI[2]);
	}
	else{
		SDL_RenderCopy(a->r, g->t[3], NULL, &g->bI[2]);
	}
	SDL_RenderCopy(a->r, g->t[0], NULL, &g->bI[0]);
	SDL_RenderCopy(a->r, g->t[1], NULL, &g->bI[1]);
	for(u8 i = 4; i < 10; i++){
		SDL_RenderCopy(a->r, g->t[i], NULL, &g->bI[i-1]);
	}
	
}

void dB(SDL_Renderer *r, const SDL_Rect *b){
	SDL_SetRenderDrawColor(r, 100, 100, 100, 255);
	for(u8 i = 0; i < 3;i++){
		SDL_RenderFillRect(r, &b[i]);
	}
	SDL_SetRenderDrawColor(r, 200, 80, 80, 255);
	for(u8 i = 3; i < 6;i++){
		SDL_RenderFillRect(r, &b[i]);
	}
	SDL_RenderFillRect(r, &b[8]);
	SDL_SetRenderDrawColor(r, 150, 150, 150, 255);
	for(u8 i = 6; i < 8;i++){
		SDL_RenderFillRect(r, &b[i]);
	}
}

void d(App *a, Graphics *g, Song *s){
	cTM(a,s);
	dB(a->r,g->bI);
	dSL(a,s);
	dBT(a,g);
}

void w(App *a, SDL_Texture **t, Song *s){
	wBN(a,s);
	wSL(a,s);
	wBT(a,t);
}
