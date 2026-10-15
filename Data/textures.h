#ifndef TEXTURES_H
#define TEXTURES_H


#include "common.h"

void wBN(App *a, Song *s);
void wSL(App *a, Song *s);
void cSL(App *a, Song *s);
void d(App *a, SDL_Texture **t, const SDL_Rect *b, Song *s);
void w(App *a, SDL_Texture **t, Song *s);

#endif