#include "overload.h"

Sprite *allsprites = NULL;

Sprite *MakeSprite(const char *name, SDL_Renderer *renderer)
{
  Sprite *sp;
  int w, h;

  sp = malloc(sizeof (Sprite));
  sp->texture = GetTexture(name, renderer);
  SDL_QueryTexture(sp->texture, NULL, NULL, &w, &h);
  sp->rect.w = w;
  sp->rect.h = h;
  sp->next = allsprites;
  sp->data = 0;
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

void SendToAll(SpriteCallback cb, const void *data)
{
  Sprite *sp;

  sp = allsprites;
  while (sp != NULL) {
    cb(sp, data);
    sp = sp->next;
  }
}

void SendUntil(SpriteCallback cb, const void *data)
{
  Sprite *sp;

  sp = allsprites;
  while (sp != NULL) {
    if (cb(sp, data)) break;
    sp = sp->next;
  }
}

int Colliding(Sprite *a, Sprite *b)
{
  SDL_Rect r1 = a->rect, r2 = b->rect;

  r1.x += 16; r1.w -= 16;
  r1.y += 16; r1.h -= 16;
  r2.x += 16; r2.w -= 16;
  r2.y += 16; r2.h -= 16;

  return (r1.x < r2.x + r2.w
	  && r1.x + r1.w > r2.x
	  && r1.y < r2.y + r2.h
	  && r1.h + r1.y > r2.y);
}

Sprite *CollidingWithAny(Sprite *sp)
{
  Sprite *allsp;

  allsp = allsprites;
  while (allsp != NULL) {
    if (allsp != sp && Colliding(sp, allsp))
      return allsp;
    allsp = allsp->next;
  }

  return NULL;
}
