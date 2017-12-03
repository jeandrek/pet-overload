#include "overload.h"
#include <time.h>

static Sprite *player;

void RandomPos(Sprite *sp)
{
  sp->rect.x = rand() % WINDOW_WIDTH;
  sp->rect.y = rand() % WINDOW_HEIGHT;
}

void InitGame(SDL_Renderer *renderer)
{
  player = MakeSprite("player", renderer);
  srand(time(NULL));
  RandomPos(MakeSprite("tree", renderer));
  RandomPos(MakeSprite("dog1", renderer));
  RandomPos(MakeSprite("cat1", renderer));
  RandomPos(MakeSprite("sheep1", renderer));
}

void UpdateGame(void)
{
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);

  if (keystate[SDL_SCANCODE_A])
    player->rect.x = (player->rect.x - SPEED) % WINDOW_WIDTH;

  if (keystate[SDL_SCANCODE_D])
    player->rect.x = (player->rect.x + SPEED) % WINDOW_WIDTH;

  if (keystate[SDL_SCANCODE_W])
    player->rect.y = (player->rect.y - SPEED) % WINDOW_HEIGHT;

  if (keystate[SDL_SCANCODE_S])
    player->rect.y = (player->rect.y + SPEED) % WINDOW_HEIGHT;

  switch (rand() % 60) {
  case 3:
    RandomPos(MakeSprite("tree", NULL));
    break;
  case 7:
    RandomPos(MakeSprite("dog1", NULL));
    break;
  case 11:
    RandomPos(MakeSprite("cat1", NULL));
    break;
  case 21:
    RandomPos(MakeSprite("sheep1", NULL));
  }
}
