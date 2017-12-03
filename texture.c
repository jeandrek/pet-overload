#include "overload.h"

#define HASHSIZE 71

static struct {
  const char *name;
  SDL_Texture *texture;
} cache[HASHSIZE] = {0};

/* Hash function is from here:
   http://stackoverflow.com/a/4384446 */

Uint8 hash(const char *s)
{
  Uint16 hashval;

  for (hashval = 0; *s; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

SDL_Texture *GetTexture(const char *name, SDL_Renderer *renderer)
{
  Uint8 hashval = hash(name);

  if (cache[hashval].texture == NULL) {
    SDL_Surface *surface;
    char path[32];

    snprintf(path, 32, "assets/%s.bmp", name);
    fprintf(stderr, "Debug: loading file %s\n", path);
    surface = SDL_LoadBMP(path);
    cache[hashval].name = name;
    cache[hashval].texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
  }

  return cache[hashval].texture;
}
