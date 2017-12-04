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
  Uint32 data;
};

typedef struct player Player;
struct player {
  SDL_Texture *texture;
  SDL_Rect rect;
  Sprite *next;
  Uint16 energy, money;
};

// game.c
Player *InitGame(SDL_Renderer *renderer);
void UpdateGame(Player *player);

// maze.c
typedef const char *Maze;
Maze *MazeGen(void);
void BuildMaze(Maze *maze, SDL_Renderer *renderer);

// hud.c
void DrawHUD(Player *player, SDL_Renderer *renderer);

// sprite.c
Sprite *MakeSprite(const char *name, SDL_Renderer *renderer);
void DestroySprite(Sprite *sp);
void DrawSprites(SDL_Renderer *renderer);
int Colliding(Sprite *a, Sprite *b);
Sprite *CollidingWithAny(Sprite *sp);

// texture.c
SDL_Texture *GetTexture(const char *name, SDL_Renderer *renderer);

// Game constants
#define WINDOW_WIDTH	640
#define WINDOW_HEIGHT	480
#ifdef DEBUG
#define WINDOW_TITLE	"Pet Overload (DEBUG)"
#else
#define WINDOW_TITLE	"Pet Overload"
#endif

#define SPEED	5

#endif /* !_OVERLOAD_H */
