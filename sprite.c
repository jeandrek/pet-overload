#include "overload.h"

Sprite *allsprites = NULL;

Sprite *MakeSprite(const char *name, SDL_Renderer *renderer)
{
  Sprite *sp;
  int w, h;

  sp = malloc(sizeof (Sprite));
  sp->texture = GetTexture(name, renderer);
  SDL_QueryTexture(sp->texture, NULL, NULL, &w, &h);
  sp->rect.x = 0;
  sp->rect.y = 0;
  sp->rect.w = w;
  sp->rect.h = h;
  sp->next = allsprites;
  allsprites = sp;

  return sp;
}

void DestroySprite(Sprite *sp)
{
  Sprite **allsp;

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

int Colliding(Sprite *a, Sprite *b)
{
  SDL_Rect ar = a->rect, br = b->rect;

  return (ar.x < br.x + br.w
	  && ar.x + ar.w > br.x
	  && ar.y < br.y + br.h
	  && ar.h + ar.y > br.y);
}

int CollidingWithAny(Sprite *sp)
{
  Sprite *allsp;

  allsp = allsprites;
  while (allsp != NULL) {
    if (allsp != sp && Colliding(sp, allsp))
      return 1;
    allsp = allsp->next;
  }

  return 0;
}
