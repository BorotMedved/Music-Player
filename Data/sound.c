#include "window.h"
#include "textures.h"
#include <dirent.h>

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
			
			strcpy(s[i].dN, e->d_name);
			char *ext = strrchr(s[i].dN, '.');
			if (ext != NULL) {
				*ext = '\0';
			}
			
			size_t len = strlen(s[i].dN);
			while (len < 15) {
				s[i].dN[len] = ' ';
				len++;
			}

			s[i].dN[len] = '\0';

			snprintf(s[i].p, sizeof(s[i].p), "Songs/%s", e->d_name);
			s[i].m = NULL;
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

void pM(App *a, Song *s){
	
	if (a->sC == 0) {
        return;
    }
	
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

        a->cS++;

        if (a->cS >= a->sC) {
            a->cS = 0;
        }

    } while (a->cS != st);

}


void pP(App *a){
	if (!Mix_PlayingMusic() && !Mix_PausedMusic()) {
        return;
    }
	a->isP = !a->isP;
	if(!a->isP){
		Mix_ResumeMusic();
	}else{
		Mix_PauseMusic();
	}
}

void fS(App *a, Song *s){
	Mix_HaltMusic();
	if (s[a->cS].m != NULL) {
        Mix_FreeMusic(s[a->cS].m);
        s[a->cS].m = NULL;
    }
	if(a->tN != NULL){
		SDL_DestroyTexture(a->tN);
		a->tN = NULL;
	}
}

void tOisP(App *a){
	if(a->isP == true){
		a->isP = false;
	}
}

void n(App *a, Song *s){
	fS(a,s);
	if(a->cS == a->sC - 1){
		a->cS = 0;
	}else{
		a->cS++;
	}
	
	pM(a,s);
	tOisP(a);

	wBN(a,s);
}

void c(App *a, Song *s, u8 sC){
	fS(a,s);
	a->cS = sC;
	pM(a,s);
	tOisP(a);
	wBN(a,s);
}

void bk(App *a, Song *s){
	fS(a,s);
	if(a->cS == 0){
		a->cS = a->sC - 1;
	}else{
		a->cS--;
	}
	
	pM(a,s);
	tOisP(a);
	
	wBN(a,s);
}

void sh(App *a, Song *s) {
	fS(a, s);
	cSL(a->sC, s);
	
    u8 count = a->sC;

    for (u8 i = count; i > 1; i--) {
        u8 r = rand() % i;

        Song t = s[i - 1];
        s[i - 1] = s[r];
        s[r] = t;
    }
	
    a->cS = 0;
	a->dC = 18;
	wSL(a,s);

    pM(a, s);
    wBN(a, s);
}

void sV(u8 *av, u8 v){
	*av = v;
	Mix_VolumeMusic(*av);
}

void aV(u8 *av){
	if(*av < 128){
		*av += 16;
		Mix_VolumeMusic(*av);
	}
}

void rV(u8 *av){
	if(*av > 0){
		*av -= 16;
		Mix_VolumeMusic(*av);
	}
}

void mU(u8 *av){
	if(*av == 0){
		sV(av,64);
	}else{
		sV(av,0);
	}
}