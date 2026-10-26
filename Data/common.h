#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

typedef struct {
	char n[256];
	char dN[256];
	char p[512];
	Mix_Music *m;
	SDL_Rect b;
	SDL_Texture *t;
} Song;

typedef struct {
	u16 w;
	u16 h;
} Resolution;

typedef struct {
	SDL_Renderer *r;
	SDL_Window *w;
	u8 cS;
	SDL_Texture *tN;
	SDL_Texture *cT;
	TTF_Font *f;
	u8 sC;
	u16 dC; 
	u8 v;
	bool l;
	bool isP;
	bool e;
} App;

typedef struct{
	SDL_Rect bS[3];
	SDL_Rect bI[10];
	SDL_Texture *t[13];
} Graphics;

#endif