#include "sound.h"
#include "window.h"
#include "textures.h"
#include <time.h>

void cU(App *a, SDL_Texture **t, Song *s){
    for (u8 i = 0; i < 10; i++) {
        SDL_DestroyTexture(t[i]);
		t[i] = NULL;
    }
	for (u8 i = 0; i < a->sC; i++) {
        SDL_DestroyTexture(s[i].t);
		s[i].t = NULL;
    }

    SDL_DestroyTexture(a->tN);
	a->tN = NULL;
    SDL_DestroyTexture(a->cT);
	a->cT = NULL;
	
	Mix_HaltMusic();

    for (u8 i = 0; i < a->sC; i++) {
        Mix_FreeMusic(s[i].m);
		s[i].m = NULL;
    }

    TTF_CloseFont(a->f);
	a->f = NULL;
	
	SDL_DestroyRenderer(a->r);
	a->r = NULL;
	
	SDL_DestroyWindow(a->w);
	a->w = NULL;

    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

void sU(App *a, Graphics *g, Song *s){
	const SDL_Rect bI[9] = {
		{4,4,64,48}, // Back
		{204,4,64,48}, // Next
		{104,4,64,48}, // Play/Pause
		{280, 16, 26, 26}, // Shuffle
		{4, 460, 16, 16}, // <-
		{32, 460, 16, 16}, // ->
		{300,460,16,16}, // +
		{280,460,16,16}, // -
		{260,460,16,16} // #
	};
	const SDL_Rect bS[3] = {
		{4, 64, 256, 32}, // Name
		{280, 64, 32,32},  // Time
		{50,460,64,16} // Song Count
	};
	
	memcpy(g->bI, bI, sizeof bI);
	memcpy(g->bS, bS, sizeof bS);
	
	srand(time(NULL));
	
	a->dC = 18;
	a->f = TTF_OpenFont("Assets/font.ttf", 8);
	
	oD(a,g->t,s);
	pM(a,s);
	w(a,g->t,s);
	sV(&a->v, 64);
}

void initSDL(App *a, Graphics *g, Song *s){
	Resolution res;
	res.w = 320;
	res.h = 480;
	
    u32 rFlags, wFlags;

    rFlags = SDL_RENDERER_ACCELERATED;

    wFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        exit(1);
    }
	
	if (TTF_Init() == -1) {
		exit(1);
	}

    a->w = SDL_CreateWindow("Music-Player", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, res.w, res.h, wFlags);

    if (!a->w)
    {
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    a->r = SDL_CreateRenderer(a->w, -1, rFlags);

    if (!a->r)
    {
        exit(1);
    }
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		exit(1);
	}
	
	sU(a,g,s);
	
}

void nL(App *a, Song *s){
	cSL(a->sC,s);
	if(a->dC < a->sC){
		a->dC += 18;
	}
	wSL(a,s);
}

void bL(App *a, Song *s){
	cSL(a->sC,s);
	if(a->dC > 0){
		a->dC -= 18;
	}
	if(a->dC <= 0){
		a->dC = 18;
	}
	wSL(a,s);
}

void lS(App *a, Song *s, SDL_Point m){
	u16 start = a->dC - 18;
	u16 end = a->dC;
	for (u16 i = start; i < end && i < a->sC; i++) {
		if(SDL_PointInRect(&m,&s[i].b)){
			c(a,s,i);
		}
	}
}

void kC(App *a, Song *s, SDL_Event e){
	if(e.key.keysym.sym == SDLK_SPACE){
		pP(a);
	}else if(e.key.keysym.sym == SDLK_LEFT){
		bk(a,s);
	}else if(e.key.keysym.sym == SDLK_RIGHT){
		n(a,s);
	}else if(e.key.keysym.sym == SDLK_s){
		sh(a,s);
	}else if(e.key.keysym.sym == SDLK_COMMA){
		rV(&a->v);
	}else if(e.key.keysym.sym == SDLK_PERIOD){
		aV(&a->v);
	}else if(e.key.keysym.sym == SDLK_HASH){
		mU(&a->v);
	}else if(e.key.keysym.sym == SDLK_a){
		bL(a,s);
	}else if(e.key.keysym.sym == SDLK_d){
		nL(a,s);
	}
}

void mC(App *a, Song *s, SDL_Event e, const SDL_Rect *b){
	SDL_Point m = {e.button.x,e.button.y};
	if(SDL_PointInRect(&m,&b[0])){
		bk(a,s);
	}else if(SDL_PointInRect(&m,&b[1])){
		n(a,s);
	}else if(SDL_PointInRect(&m,&b[2])){
		pP(a);
	}else if(SDL_PointInRect(&m,&b[3])){
		sh(a,s);
	}else if(SDL_PointInRect(&m,&b[4])){
		bL(a,s);
	}else if(SDL_PointInRect(&m,&b[5])){
		nL(a,s);
	}else if(SDL_PointInRect(&m,&b[6])){
		aV(&a->v);
	}else if(SDL_PointInRect(&m,&b[7])){
		rV(&a->v);
	}else if(SDL_PointInRect(&m,&b[8])){
		mU(&a->v);
	}else{
		lS(a,s,m);
	}
	
}

void dI(App *a, Graphics *g, Song *s){
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
			case SDL_KEYDOWN:
				kC(a,s,e);
				break;
			
            case SDL_QUIT:
				cU(a,g->t,s);
				exit(0);
                break;
				
			case SDL_MOUSEBUTTONDOWN:
				mC(a,s,e,g->bI);
				break; 
				
            default:
                break;
        }
    }
}

void pPS(SDL_Renderer *r){
	SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderClear(r);
}

void r(App *a, Graphics *g,Song *s){
	pPS(a->r);
	d(a, g, s);
	dI(a,g,s);
	SDL_RenderPresent(a->r);
	SDL_Delay(16);
	if(Mix_PlayingMusic() == 0 && Mix_PausedMusic() != 1){
		n(a,s);
	}
}