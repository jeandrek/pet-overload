#include "overload.h"

static Sprite *player;

void InitGame(void)
{
  player = MakeSprite("player");
}

void UpdateGame(void)
{
  const Uint8 *keystate;

  keystate = SDL_GetKeyboardState(NULL);

  if (keystate[SDL_SCANCODE_LEFT])
    player->rect.x = (player->rect.x - SPEED) % WINDOW_WIDTH;

  if (keystate[SDL_SCANCODE_RIGHT])
    player->rect.x = (player->rect.x + SPEED) % WINDOW_WIDTH;

  if (keystate[SDL_SCANCODE_UP])
    player->rect.y = (player->rect.y - SPEED) % WINDOW_HEIGHT;

  if (keystate[SDL_SCANCODE_DOWN])
    player->rect.y = (player->rect.y + SPEED) % WINDOW_HEIGHT;
}
