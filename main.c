#include "overload.h"

int main(int argc, char *argv[])
{
  SDL_Window *window;
  SDL_Surface *surface, *bgsurface;
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

  surface = SDL_GetWindowSurface(window);
  bgsurface = SDL_LoadBMP("assets/background.bmp");

  InitGame();

  for (;;) {
    while (!SDL_PollEvent(&ev)) {
      switch (ev.type) {
      case SDL_QUIT:
	goto quit;
      }
    }

    UpdateGame();
    SDL_BlitSurface(bgsurface, NULL, surface, NULL);
    DrawSprites(surface);
    SDL_UpdateWindowSurface(window);
  }
 quit:
  SDL_FreeSurface(bgsurface);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
