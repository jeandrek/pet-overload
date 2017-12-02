#include "overload.h"

int main(int argc, char *argv[])
{
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Surface *bgsurface;
  SDL_Texture *bgtexture;
  SDL_Event ev;

  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  window = SDL_CreateWindow("Pet Overload", SDL_WINDOWPOS_UNDEFINED,
			    SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
			    WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if (!window) {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  bgsurface = SDL_LoadBMP("assets/background.bmp");
  bgtexture = SDL_CreateTextureFromSurface(renderer, bgsurface);
  SDL_FreeSurface(bgsurface);

  InitGame(renderer);

  for (;;) {
    while (!SDL_PollEvent(&ev)) {
      switch (ev.type) {
      case SDL_QUIT:
	goto quit;
      }
    }

    UpdateGame();
    SDL_RenderCopy(renderer, bgtexture, NULL, NULL);
    DrawSprites(renderer);
    SDL_RenderPresent(renderer);
  }
 quit:
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  return EXIT_SUCCESS;
}
