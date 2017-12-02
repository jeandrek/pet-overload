#include "overload.h"
#include <time.h>

static Sprite *player;

void RandomPos(Sprite *sp)
{
  sp->rect.x = rand() % WINDOW_WIDTH;
  sp->rect.y = rand() % WINDOW_HEIGHT;
}

void InitGame(void)
{
  player = MakeSprite("player");
  {
    Sprite *d1, *d2, *c1, *c2;
    srand(time(NULL));
    d1 = MakeSprite("dog1");
    d2 = MakeSprite("dog1");
    c1 = MakeSprite("cat1");
    c2 = MakeSprite("cat1");
    RandomPos(d1), RandomPos(d2);
    RandomPos(c1), RandomPos(c2);
  }
}

void UpdateGame(void)
{
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);

  if (keystate[SDL_SCANCODE_LEFT])
    player->rect.x = (player->rect.x - SPEED) % WINDOW_WIDTH;

  if (keystate[SDL_SCANCODE_RIGHT])
    player->rect.x = (player->rect.x + SPEED) % WINDOW_WIDTH;

  if (keystate[SDL_SCANCODE_UP])
    player->rect.y = (player->rect.y - SPEED) % WINDOW_HEIGHT;

  if (keystate[SDL_SCANCODE_DOWN])
    player->rect.y = (player->rect.y + SPEED) % WINDOW_HEIGHT;
}
