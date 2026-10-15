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

void sU(App *a, SDL_Texture **t, Song *s){
	srand(time(NULL));
	a->dC = 18;
	a->f = TTF_OpenFont("Assets/font.ttf", 8);
	oD(a,t,s);
	pM(a,s);
	w(a,t,s);
	sV(a, 64);
}

void initSDL(App *a, SDL_Texture **t, Song *s){
	Resolution res;
	res.w = 320;
	res.h = 480;
	
    u32 rFlags, wFlags;

    rFlags = SDL_RENDERER_ACCELERATED;

    wFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
	
	if (TTF_Init() == -1) {
		printf("TTF_Init failed: %s\n", TTF_GetError());
	}

    a->w = SDL_CreateWindow("Music-Player", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, res.w, res.h, wFlags);

    if (!a->w)
    {
        printf("Failed to open %d x %d w: %s\n", res.w, res.h, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    a->r = SDL_CreateRenderer(a->w, -1, rFlags);

    if (!a->r)
    {
        printf("Failed to create r: %s\n", SDL_GetError());
        exit(1);
    }
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("Mixer failed: %s\n", Mix_GetError());
	}
	
	sU(a,t,s);
	
}

void nL(App *a, Song *s){
	cSL(a,s);
	if(a->dC < a->sC){
		a->dC += 18;
	}
	wSL(a,s);
}

void bL(App *a, Song *s){
	cSL(a,s);
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
		rV(a);
	}else if(e.key.keysym.sym == SDLK_PERIOD){
		aV(a);
	}else if(e.key.keysym.sym == SDLK_HASH){
		m(a);
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
	}else if(SDL_PointInRect(&m,&b[5])){
		sh(a,s);
	}else if(SDL_PointInRect(&m,&b[6])){
		bL(a,s);
	}else if(SDL_PointInRect(&m,&b[7])){
		nL(a,s);
	}else if(SDL_PointInRect(&m,&b[9])){
		aV(a);
	}else if(SDL_PointInRect(&m,&b[10])){
		rV(a);
	}else{
		lS(a,s,m);
	}
	
}

void dI(App *a, const SDL_Rect *b, Song *s, SDL_Texture **t){
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
			case SDL_KEYDOWN:
				kC(a,s,e);
				break;
			
            case SDL_QUIT:
				cU(a,t,s);
				exit(0);
                break;
				
			case SDL_MOUSEBUTTONDOWN:
				mC(a,s,e,b);
				break; 
				
            default:
                break;
        }
    }
}

void pPS(App *a){
	SDL_SetRenderDrawColor(a->r, 0, 0, 0, 255);
    SDL_RenderClear(a->r);
}

void r(App *a,SDL_Texture **t,const SDL_Rect *b,Song *s){
	pPS(a);
	d(a, t, b, s);
	dI(a,b,s, t);
	SDL_RenderPresent(a->r);
	SDL_Delay(16);
	if(Mix_PlayingMusic() == 0 && Mix_PausedMusic() != 1){
		n(a,s);
	}
}