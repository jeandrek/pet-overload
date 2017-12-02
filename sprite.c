#include "overload.h"

Sprite *allsprites = NULL;

Sprite *MakeSprite(const char *name)
{
  char texture[32];
  Sprite *sp;

  snprintf(texture, 32, "assets/%s.bmp", name);
  fprintf(stderr, "Debug: loading file %s\n", texture);

  sp = malloc(sizeof (Sprite));
  sp->surface = SDL_LoadBMP(texture);
  sp->rect.x = 0;
  sp->rect.y = 0;
  sp->next = allsprites;
  allsprites = sp;

  return sp;
}

void DestroySprite(Sprite *sp)
{
  Sprite **allsp;

  SDL_FreeSurface(sp->surface);

  // Remove sprite from list
  allsp = &allsprites;
  while (*allsp != sp)
    allsp = &(*allsp)->next;
  *allsp = sp->next;

  free(sp);
}

void DrawSprites(SDL_Surface *surface)
{
  Sprite *sp;

  sp = allsprites;
  while (sp != NULL) {
    SDL_BlitSurface(sp->surface, NULL, surface, &sp->rect);
    sp = sp->next;
  }
}
