#include "overload.h"

static Sprite *player;

void InitGame(void)
{
  player = MakeSprite("player");
  {
    Sprite *d1, *d2;
    srand(time(NULL));
    d1 = MakeSprite("dog1");
    d2 = MakeSprite("dog1");
    d1->rect.x = rand() % WINDOW_WIDTH;
    d1->rect.y = rand() % WINDOW_HEIGHT;
    d2->rect.x = rand() % WINDOW_WIDTH;
    d2->rect.y = rand() % WINDOW_HEIGHT;
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
