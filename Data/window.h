#ifndef WINDOW_H
#define WINDOW_H


#include "common.h"

void cU(App *a, SDL_Texture **t, Song *s);
void initSDL(App *a,SDL_Texture **t, Song *S);
void r(App *a,SDL_Texture **t,const SDL_Rect *b,Song *s);

#endif