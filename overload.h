#ifndef _OVERLOAD_H
#define _OVERLOAD_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct sprite Sprite;

struct sprite {
  SDL_Texture *texture;
  SDL_Rect rect;
  Sprite *next;
};

// game.c
void InitGame(SDL_Renderer *renderer);
void UpdateGame(void);

// sprite.c
Sprite *MakeSprite(const char *name, SDL_Renderer *renderer);
void DestroySprite(Sprite *sp);
void DrawSprites(SDL_Renderer *renderer);

// texture.c
SDL_Texture *GetTexture(const char *name, SDL_Renderer *renderer);

// Game constants
#define WINDOW_WIDTH	640
#define WINDOW_HEIGHT	480

#define SPEED	5

#endif /* !_OVERLOAD_H */