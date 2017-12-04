#include "overload.h"

void RandomPos(Sprite *sp)
{
  sp->rect.x = rand() % WINDOW_WIDTH;
  sp->rect.y = rand() % WINDOW_HEIGHT;
}

Player *InitGame(SDL_Renderer *renderer)
{
  Player *player = (Player *)MakeSprite("player", renderer);

  BuildMaze(MazeGen(), renderer);

  GetTexture("npc", renderer);
  player->energy = 100;
  player->money = 1337;

  return player;
}

Sprite *Move(Sprite *a, Uint8 left, Uint8 right, Uint8 up, Uint8 down)
{
  SDL_Rect delta = {0,0,0,0};
  Sprite *b;

  if (left)  delta.x = -SPEED;
  if (right) delta.x = +SPEED;
  if (up)    delta.y = -SPEED;
  if (down)  delta.y = +SPEED;

  a->rect.x += delta.x;
  a->rect.y += delta.y;

  if ((b = CollidingWithAny(a))) {
    a->rect.x -= delta.x;
    a->rect.y -= delta.y;
  }

  return b;
}

void UpdateGame(Player *player)
{
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  Sprite *met;

  player->money--;

  met = Move((Sprite *)player,
	     state[SDL_SCANCODE_A], state[SDL_SCANCODE_D],
	     state[SDL_SCANCODE_W], state[SDL_SCANCODE_S]);

  if (met && met->data == 1) {
    met->data |= 0b10;
    met->texture = GetTexture("npc", NULL);
    player->energy -= 10;
  }
}
