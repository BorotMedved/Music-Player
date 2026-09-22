#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include <dirent.h>
#include <windows.h>
#include <psapi.h>
#include <stdlib.h>
#include <time.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef struct {
	u16 w;
	u8 h;
} Resolution;

typedef struct {
	SDL_Renderer *r;
	SDL_Window *w;
	bool isP;
	u8 cS;
	SDL_Texture *tN;
	SDL_Texture *cT;
	TTF_Font *f;
} App;

typedef struct {
	char n[256];
	char p[512];
	Mix_Music *m;
	u8 sC;
} Song;

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

void oD(App *a, SDL_Texture **t, Song *s){
	
	DIR *dir = opendir("Songs");

    if (dir == NULL) {
        printf("Could not open Songs folder\n");
		cU(a,t,s);
		exit(0);
    }
	
	struct dirent *e;
	
	u8 i = 0;
	while((e = readdir(dir)) != NULL){
		if(strstr(e->d_name, ".mp3") != NULL){
			strcpy(s[i].n,e->d_name);
			snprintf(s[i].p,sizeof(s[i].p),"Songs/%s",e->d_name);
			i++;
		}
	}
	s->sC = i;
	
	if(s->sC == 0){
		cU(a,t,s);
		exit(0);
	}
	
	closedir(dir);
	
}

void pM(App *a, Song *s)
{
	u8 st = a->cS;
	
	do {
        if (s[a->cS].m != NULL) {
            Mix_FreeMusic(s[a->cS].m);
            s[a->cS].m = NULL;
        }

        s[a->cS].m = Mix_LoadMUS(s[a->cS].p);

        if (s[a->cS].m != NULL) {
            Mix_PlayMusic(s[a->cS].m, 1);
            return;
        }

        printf("Failed to load: %s\n", s[a->cS].p);

        a->cS++;

        if (a->cS >= s->sC) {
            a->cS = 0;
        }

    } while (a->cS != st);

	printf("Could not load any songs.\n");
}

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


void pP(App *a){
	a->isP = !a->isP;
					if(!a->isP){
						Mix_ResumeMusic();
					}else{
						Mix_PauseMusic();
					}
}

void n(App *a, Song *s){
	Mix_HaltMusic();
					
					if(a->cS == s->sC - 1){
						a->cS = 0;
					}else{
						a->cS++;
					}
					
					pM(a,s);
					if(a->isP == true){
						a->isP = false;
					}
					
					SDL_DestroyTexture(a->tN);
					wBN(a,s);
}

void bk(App *a, Song *s){
	
	
	
	Mix_HaltMusic();
					
					if(a->cS == 0){
						a->cS = s->sC - 1;
					}else{
						a->cS--;
					}
					
					pM(a,s);
					if(a->isP == true){
						a->isP = false;
					}
					
					SDL_DestroyTexture(a->tN);
					wBN(a,s);
}

void sh(App *a, Song *s){
	
	 u8 count = s->sC;
	
	for(u8 i = 0; i < s->sC;i++){
		u8 r = rand() % s->sC;
		if(i == r){
			continue;
		}
		Song t = s[i];
		s[i] = s[r];
		s[r] = t;
	}
	
	s[0].sC = count;
	
	Mix_HaltMusic();
	a->cS = 0;
	pM(a, s);
	SDL_DestroyTexture(a->tN);
	wBN(a, s);
	
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

void ppS(App *a)
{
    SDL_SetRenderDrawColor(a->r, 0, 0, 0, 255);
    SDL_RenderClear(a->r);
}

void psS(App *a)
{
    SDL_RenderPresent(a->r);
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

int main(){
	App a = {0};
	
	srand(time(NULL));
	
	memset(&a, 0, sizeof(App));
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