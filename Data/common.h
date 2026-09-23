#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <windows.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

typedef struct {
	char n[256];
	char p[512];
	Mix_Music *m;
	u8 sC;
} Song;

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

#endif