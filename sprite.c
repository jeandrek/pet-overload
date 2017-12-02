#include "overload.h"

Sprite *allsprites = NULL;

Sprite *MakeSprite(const char *name, SDL_Renderer *renderer)
{
  SDL_Surface *surface;
  char path[32];
  Sprite *sp;

  snprintf(path, 32, "assets/%s.bmp", name);
  fprintf(stderr, "Debug: loading file %s\n", path);
  surface = SDL_LoadBMP(path);

  sp = malloc(sizeof (Sprite));
  sp->texture = SDL_CreateTextureFromSurface(renderer, surface);
  sp->rect.x = 0;
  sp->rect.y = 0;
  sp->rect.w = 48;
  sp->rect.h = 48;
  sp->next = allsprites;
  allsprites = sp;
  SDL_FreeSurface(surface);

  return sp;
}

void DestroySprite(Sprite *sp)
{
  Sprite **allsp;

  SDL_DestroyTexture(sp->texture);

  // Remove sprite from list
  allsp = &allsprites;
  while (*allsp != sp)
    allsp = &(*allsp)->next;
  *allsp = sp->next;

  free(sp);
}

void DrawSprites(SDL_Renderer *renderer)
{
  Sprite *sp;

  sp = allsprites;
  while (sp != NULL) {
    SDL_RenderCopy(renderer, sp->texture, NULL, &sp->rect);
    sp = sp->next;
  }
}
