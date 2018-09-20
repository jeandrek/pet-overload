#include "overload.h"

void DrawText(SDL_Renderer *renderer, const char *text, Uint16 x, Uint16 y);

void DrawHUD(SDL_Renderer *renderer, Player *player)
{
  SDL_Rect hudbox = {0, WINDOW_HEIGHT - 45, WINDOW_WIDTH, 45};
  char hud1[12], hud2[16];

  SDL_SetRenderDrawColor(renderer, 0xc0, 0xe0, 0xf0, 0xff);
  SDL_RenderFillRect(renderer, &hudbox);

  if (gameover) {
    DrawText(renderer, "Game over!", WINDOW_WIDTH/3, hudbox.y + 5);
    return;
  }

  snprintf(hud1, 12, "Energy %hu", player->energy);
  snprintf(hud2, 16, "Money $%hu", player->money);

  DrawText(renderer, hud1, 5, hudbox.y + 5);
  DrawText(renderer, hud2, WINDOW_WIDTH/2 + 5, hudbox.y + 5);
}

void DrawText(SDL_Renderer *renderer, const char *text, Uint16 x, Uint16 y)
{
  SDL_Texture *font;

  font = GetTexture("font", renderer);

  while (*text > 0) {
    SDL_Rect b, p;

    switch (*text++) {
    case 'E': b = (SDL_Rect){3, 0, 36, 56}; break;
    case 'n': b = (SDL_Rect){42, 8, 32, 56}; break;
    case 'e': b = (SDL_Rect){79, 6, 34, 56}; break;
    case 'r': b = (SDL_Rect){119, 4, 42, 56}; break;
    case 'g': b = (SDL_Rect){165, 7, 31, 70}; break;
    case 'y': b = (SDL_Rect){205, 8, 36, 70}; break;
    case 'M': b = (SDL_Rect){1, 56, 41, 56}; break;
    case 'o': b = (SDL_Rect){51, 64, 38, 56}; break;
    case 'G': b = (SDL_Rect){10, 173, 44, 56}; break;
    case 'a': b = (SDL_Rect){61, 172, 38, 56}; break;
    case 'm': b = (SDL_Rect){108, 187, 45, 56}; break;
    case 'v': b = (SDL_Rect){190,182, 34,57}; break;
    case '0': b = (SDL_Rect){100, 75, 48, 56}; break;
    case '1': b = (SDL_Rect){149, 76, 39, 56}; break;
    case '2': b = (SDL_Rect){187, 78, 47, 56}; break;
    case '3': b = (SDL_Rect){234, 74, 42, 56}; break;
    case '4': b = (SDL_Rect){252, 11, 39, 56}; break;
    case '5': b = (SDL_Rect){0, 119, 43, 56}; break;
    case '6': b = (SDL_Rect){49, 118, 40, 56}; break;
    case '7': b = (SDL_Rect){94, 132, 45, 56}; break;
    case '8': b = (SDL_Rect){142, 134, 43, 56}; break;
    case '9': b = (SDL_Rect){194, 134, 43, 56}; break;
    case '$': b = (SDL_Rect){239, 130, 38, 60}; break;
    case '!': b = (SDL_Rect){272, 174, 14, 56}; break;
    case ' ': x += 32; continue;
    }

    p.x = x;
    p.y = y;
    p.w = b.w/2;
    p.h = b.h/2;
    x += p.w;

    SDL_RenderCopy(renderer, font, &b, &p);
  }
}
