#include "window.h"
#include "textures.h"
#include <dirent.h>

void displayNameFixing(struct dirent *e, Song *s, u8 j){
	strcpy(s[j].dN, e->d_name);
	char *ext = strrchr(s[j].dN, '.');
	if (ext != NULL) {
		*ext = '\0';
	}
	
	size_t len = strlen(s[j].dN);
    while (len < 15) {
        s[j].dN[len] = ' ';
        len++;
    }

    s[j].dN[len] = '\0';
}

void oD(App *a, SDL_Texture **t, Song *s){
	
	DIR *dir = opendir("Songs");

    if (dir == NULL) {
		cU(a,t,s);
		exit(0);
    }
	
	struct dirent *e;
	
	u8 i = 0;
	while((e = readdir(dir)) != NULL){
		if(strstr(e->d_name, ".mp3") != NULL || strstr(e->d_name, ".flac") != NULL || strstr(e->d_name, ".wav") != NULL){
			strcpy(s[i].n, e->d_name);
			
			displayNameFixing(e,s,i);

			snprintf(s[i].p, sizeof(s[i].p), "Songs/%s", e->d_name);
			i++;
		}
	}
	a->sC = i;
	
	if(a->sC == 0){
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

        SDL_RWops *rw = SDL_RWFromFile(s[a->cS].p, "rb");

		if (rw != NULL) {
			s[a->cS].m = Mix_LoadMUSType_RW(rw, MUS_NONE, 1);
		} else {
			s[a->cS].m = NULL;
		}

        if (s[a->cS].m != NULL) {
            Mix_PlayMusic(s[a->cS].m, 1);
            return;
        }
		
		printf("FAILED TO LOAD: %s\n", s[a->cS].p);
        printf("Mixer error: %s\n", Mix_GetError());

        a->cS++;

        if (a->cS >= a->sC) {
            a->cS = 0;
        }

    } while (a->cS != st);

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
					
					if(a->cS == a->sC - 1){
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

void c(App *a, Song *s, u8 sC){
	Mix_HaltMusic();
	a->cS = sC;
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
						a->cS = a->sC - 1;
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

void sh(App *a, Song *s) {
    u8 count = a->sC;

    for (u8 i = count; i > 1; i--) {
        u8 r = rand() % i;

        Song t = s[i - 1];
        s[i - 1] = s[r];
        s[r] = t;
    }

    Mix_HaltMusic();
    a->cS = 0;
	wSL(a,s);
	a->dC = 18;

    pM(a, s);

    SDL_DestroyTexture(a->tN);
    wBN(a, s);
}

void sV(App *a, u8 v){
	a->v = v;
	Mix_VolumeMusic(a->v);
}

void aV(App *a){
	if(a->v < 128){
		a->v += 16;
		Mix_VolumeMusic(a->v);
	}
}

void rV(App *a){
	if(a->v > 0){
		a->v -= 16;
		Mix_VolumeMusic(a->v);
	}
}

void m(App *a){
	if(a->v == 0){
		sV(a,64);
	}else{
		sV(a,0);
	}
}