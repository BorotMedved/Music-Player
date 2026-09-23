#include "sound.h"

void cU(App *a, SDL_Texture **t, Song *s)
{
    for (u8 i = 0; i < 5; i++) {
        SDL_DestroyTexture(t[i]);
		t[i] = NULL;
    }

    SDL_DestroyTexture(a->tN);
	a->tN = NULL;
    SDL_DestroyTexture(a->cT);
	a->cT = NULL;

    for (u8 i = 0; i < s->sC; i++) {
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

void initSDL(App *a)
{
	Resolution res;
	res.w = 320;
	res.h = 100;
	
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
}

void ppS(App *a)
{
    SDL_SetRenderDrawColor(a->r, 0, 0, 0, 255);
    SDL_RenderClear(a->r);
}

void psS(App *a)
{
    SDL_RenderPresent(a->r);
}

void dI(App *a, const SDL_Rect *b, Song *s, SDL_Texture **t)
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
			case SDL_KEYDOWN:
				if(e.key.keysym.sym == SDLK_SPACE){
					pP(a);
				}else if(e.key.keysym.sym == SDLK_LEFT){
					bk(a,s);
				}else if(e.key.keysym.sym == SDLK_RIGHT){
					n(a,s);
				}else if(e.key.keysym.sym == SDLK_s){
					sh(a,s);
					
				}
				break;
			
            case SDL_QUIT:
				cU(a,t,s);
				exit(0);
                break;
				
			case SDL_MOUSEBUTTONDOWN:
				SDL_Point m = {e.button.x,e.button.y};
				if(SDL_PointInRect(&m,&b[0])){
					bk(a,s);
				}
				if(SDL_PointInRect(&m,&b[1])){
					n(a,s);
				}
				if(SDL_PointInRect(&m,&b[2])){
					pP(a);
				}
				if(SDL_PointInRect(&m,&b[5])){
					sh(a,s);
				}
				break;
				
            default:
                break;
        }
    }
}
