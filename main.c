#include "overload.h"

/* Kludge to get it to work optimally on MS Windows:
   Use WinMain if and only if we are on Windows and
   this is not a debug build. */
#if defined(_WIN32) && !defined(DEBUG)
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,
		   LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char *argv[])
#endif
{
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *bgtexture;
  SDL_Event ev;

  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  window = SDL_CreateWindow("Pet Overload", SDL_WINDOWPOS_CENTERED,
			    SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
			    WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if (!window) {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  bgtexture = GetTexture("background", renderer);

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
    DrawHUD(renderer);
    SDL_RenderPresent(renderer);
  }

 quit:
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  return EXIT_SUCCESS;
}
