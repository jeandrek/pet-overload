#ifndef _OVERLOAD_H
#define _OVERLOAD_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

// Game constants
#define WINDOW_WIDTH	640
#define WINDOW_HEIGHT	480
#ifdef DEBUG
#define WINDOW_TITLE	"Pet Overload (DEBUG)"
#else
#define WINDOW_TITLE	"Pet Overload"
#endif
#define MAP_WIDTH	14
#define MAP_HEIGHT	10
#define SPEED		5
#define MASK_ANIMAL	((Uint32)1<<31)
#define MASK_PET	((Uint32)1<<30)
#define MASK_SOLD	((Uint32)1<<29)
#define MASK_NPC	((Uint32)1<<28)
#define MASK_EXIT	((Uint32)1<<27)

// Global variables
const char *startmap;
Uint8 gameover;

// Type definitions
typedef struct sprite Sprite;
typedef struct player Player;
typedef int (*SpriteCallback)(Sprite *, const void *);

struct sprite {
  SDL_Texture *texture;
  SDL_Rect rect;
  Sprite *next;
  Uint32 data;
};

struct player {
  SDL_Texture *texture;
  SDL_Rect rect;
  Sprite *next;
  short energy, money;
};

// game.c
Player *InitGame(SDL_Renderer *renderer);
void UpdateGame(SDL_Renderer *renderer, Player *player);

// map.c
typedef char *Map;
Map *LoadMap(const char *name);
void BuildMap(Map *map, SDL_Renderer *renderer);

// hud.c
void DrawHUD(SDL_Renderer *renderer, Player *player);

// sprite.c
Sprite *MakeSprite(const char *name, SDL_Renderer *renderer);
void DestroySprite(Sprite *sp);
void DrawSprites(SDL_Renderer *renderer);
void SendToAll(SpriteCallback cb, const void *data);
int SendUntil(SpriteCallback cb, const void *data);
int Colliding(Sprite *a, Sprite *b);
Sprite *CollidingWithAny(Sprite *sp);

// texture.c
SDL_Texture *GetTexture(const char *name, SDL_Renderer *renderer);

#endif /* !_OVERLOAD_H */
