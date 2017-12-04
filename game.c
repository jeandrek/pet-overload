#include "overload.h"

static Map *currentmap;

void RandomPos(Sprite *sp)
{
  sp->rect.x = rand() % WINDOW_WIDTH;
  sp->rect.y = rand() % WINDOW_HEIGHT;
}

Player *InitGame(SDL_Renderer *renderer)
{
  Player *player = (Player *)MakeSprite("player", renderer);

  BuildMap((currentmap = LoadMap(startmap)), renderer);
  GetTexture("lost", renderer);
  player->rect.x = 5;
  player->rect.y = 5;
  player->energy = 60;
  player->money = 15;

  return player;
}

Sprite *Move(Sprite *a, Uint8 left, Uint8 right, Uint8 up, Uint8 down)
{
  SDL_Rect delta = {0,0,0,0};
  Sprite *b;

  if (left)   delta.x = -SPEED;
  if (right) {delta.x = +SPEED; goto end;}
  if (up)     delta.y = -SPEED;
  if (down)   delta.y = +SPEED;
 end:
  a->rect.x += delta.x;
  a->rect.y += delta.y;

  if ((b = CollidingWithAny(a))
      // Allow pets but not players to go off-screen
      || (!(a->data & MASK_PET)
	  && (a->rect.x < 0 || a->rect.y < 0
	      || a->rect.x > WINDOW_WIDTH
	      || a->rect.y > WINDOW_HEIGHT))) {
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
  if (pet->data & MASK_PET) {
    Move(pet, state[SDL_SCANCODE_A], state[SDL_SCANCODE_D],
	 state[SDL_SCANCODE_W], state[SDL_SCANCODE_S]);
  }
}

int SellPet(Sprite *pet, Player *player)
{
  if (pet->data & MASK_PET) {
    pet->data ^= MASK_PET;
    pet->data |= MASK_SOLD;
    player->money += 90+(rand()%20);
    player->energy += 10;
    return 1;
  }
  return 0;
}

void ClearMap(Sprite *sp, Player *player)
{
  // Leave only the player and pets
  if (!sp->data || sp->data == MASK_ANIMAL
      || sp->data == (MASK_ANIMAL | MASK_SOLD)
      || sp->data == MASK_NPC
      || sp->data == MASK_EXIT)
    DestroySprite(sp);
  else if (sp->data & MASK_PET) {
    // Keep pets same distance relative to player
    sp->rect.x = 5 + (sp->rect.x - player->rect.x);
    sp->rect.y = 5 + (sp->rect.y - player->rect.y);
  }
}

void UpdateGame(SDL_Renderer *renderer, Player *player)
{
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  Sprite *met;

  met = Move((Sprite *)player,
	     state[SDL_SCANCODE_A], state[SDL_SCANCODE_D],
	     state[SDL_SCANCODE_W], state[SDL_SCANCODE_S]);

  SendToAll((SpriteCallback)Follow, state);

  if (met) {
    switch (met->data) {
    case MASK_ANIMAL:
      // Adopt animal
      met->data |= MASK_PET;
      player->energy -= 10;
      if (player->energy <= 0)
	GameOver(player);
      break;
    case MASK_NPC:
      // Sell pet to NPC
      SendUntil((SpriteCallback)SellPet, player);
      break;
    case MASK_EXIT:
      // Load next level
      SendToAll((SpriteCallback)ClearMap, player);
      player->rect.x = 5;
      player->rect.y = 5;
      BuildMap((currentmap = LoadMap(currentmap[10])), renderer);
      break;
    }
  }
}
