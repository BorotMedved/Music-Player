#include "window.h"
#include "textures.h"
#include <dirent.h>

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
		if(strstr(e->d_name, ".mp3") != NULL || strstr(e->d_name, ".flac") != NULL || strstr(e->d_name, ".wav")){
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