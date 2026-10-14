#ifndef WINDOW_H
#define WINDOW_H


#include "common.h"

void cU(App *a, SDL_Texture **t, Song *s);
void initSDL(App *a);
void ppS(App *a);
void psS(App *a);
void dI(App *a, const SDL_Rect *b, Song *s, SDL_Texture **t);

#endif