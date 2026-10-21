#ifndef TEXTURES_H
#define TEXTURES_H

#include "common.h"

void wBN(App *a, Song *s);
void wSL(App *a, Song *s);
void cSL(u8 sC, Song *s);
void d(App *a, Graphics *g, Song *s);
void w(App *a, SDL_Texture **t, Song *s);

#endif