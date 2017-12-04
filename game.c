#include "overload.h"

Uint8 gameover = 0;

void RandomPos(Sprite *sp)
{
  sp->rect.x = rand() % WINDOW_WIDTH;
  sp->rect.y = rand() % WINDOW_HEIGHT;
}

Player *InitGame(SDL_Renderer *renderer)
{
  Player *player = (Player *)MakeSprite("player", renderer);

  BuildMaze(MazeGen(), renderer);

  GetTexture("lost", renderer);
  player->energy = 60;
  player->money = 15;

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

void GameOver(Player *player)
{
  player->texture = GetTexture("lost", NULL);
  gameover = 1;
}

void Follow(Sprite *pet, Uint8 *state)
{
  if (pet->data & 1<<30) {
    Move(pet, state[SDL_SCANCODE_A], state[SDL_SCANCODE_D],
	 state[SDL_SCANCODE_W], state[SDL_SCANCODE_S]);
  }
}

void UpdateGame(Player *player)
{
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  Sprite *met;

  met = Move((Sprite *)player,
	     state[SDL_SCANCODE_A], state[SDL_SCANCODE_D],
	     state[SDL_SCANCODE_W], state[SDL_SCANCODE_S]);

  SendToAll((SpriteCallback)Follow, state);

  if (met && met->data == 1<<31) {
    met->data |= 1<<30;
    player->energy -= 10;

    if (player->energy <= 0)
      GameOver(player);
  }
}
