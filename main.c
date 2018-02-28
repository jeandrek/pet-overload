#include "overload.h"

#ifdef MACOS
#include <CoreFoundation/CoreFoundation.h>
#endif

static void LocateAssets(void)
{
#ifndef MACOS
  strcpy(assetspath, "assets");
#else
  CFBundleRef bundle;
  CFURLRef url;
  Boolean success;
  char bundlepath[128];

  bundle = CFBundleGetMainBundle();
  url = CFBundleCopyBundleURL(bundle);
  success = CFURLGetFileSystemRepresentation(url, true, (UInt8 *)bundlepath, 128);

  if (!success) {
    fprintf(stderr, "Error: Can't get bundle path\n");
    exit(EXIT_FAILURE);
  }

  snprintf(assetspath, 128, "%s/Contents/Resources", bundlepath);
#endif
}

#if defined(_WIN32) && !defined(DEBUG)
#include <windows.h>
/* Kludge to get it to work optimally on MS Windows:
   Use WinMain if and only if we are on Windows and
   this is not a debug build. */
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
  Uint32 ticks = 0;
  Player *player;

  // Initialise globals
  startmap = "level1";
  gameover = 0;

#ifdef DEBUG
  if (argc >= 3 && !strcmp(argv[1], "-map"))
    startmap = argv[2];
#endif

  LocateAssets();

  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
			    SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
			    WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if (!window) {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  bgtexture = GetTexture("background", renderer);

  player = InitGame(renderer);

  for (;;) {
    if (!SDL_PollEvent(&ev)) {
      switch (ev.type) {
      case SDL_QUIT:
	goto quit;
      }
    }

    // Run at as close to 40 FPS as possible
    if ((SDL_GetTicks()-ticks) >= 25 && !gameover) {
      UpdateGame(renderer, player);
      SDL_RenderCopy(renderer, bgtexture, NULL, NULL);
      DrawSprites(renderer);
      DrawHUD(renderer, player);
      SDL_RenderPresent(renderer);
      ticks = SDL_GetTicks();
    } else {
      SDL_Delay(5); // Idle
    }
  }

 quit:
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  return EXIT_SUCCESS;
}
