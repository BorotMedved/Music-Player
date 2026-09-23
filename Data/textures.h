#ifndef TEXTURES_H
#define TEXTURES_H


#include "common.h"

void wBN(App *a, Song *s);
void wBT(App *a, SDL_Texture **t);
void cTM(App *a, Song *s);
TTF_Font *lF();
void dBT(App *a, SDL_Texture **t, const SDL_Rect *b);
void dB(App *a, const SDL_Rect *b);
void d(App *a, SDL_Texture **t, const SDL_Rect *b);

#endif