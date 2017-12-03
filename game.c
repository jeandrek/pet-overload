#include "overload.h"
#include <time.h>

static Sprite *player;

void RandomPos(Sprite *sp)
{
  sp->rect.x = rand() % WINDOW_WIDTH;
  sp->rect.y = rand() % WINDOW_HEIGHT;
}

void InitGame(SDL_Renderer *renderer)
{
  Maze *maze = MazeGen();

  player = MakeSprite("player", renderer);

  srand(time(NULL));

  for (int y = 9; y > -1; y--) {
    for (int x = 0; x < 13; x++) {
      switch (maze[y][x]) {
      case '-':
	{
	  Sprite *tree = MakeSprite("tree", renderer);
	  tree->rect.x = x*48;
	  tree->rect.y = y*48;
	  tree->rect.x += (rand()%12)-6;
	  tree->rect.y += (rand()%12)-6;
	  break;
	}
      case 'a':
	{
	  const char *types[] = {"dog1", "cat1", "sheep1"};
	  Sprite *pet = MakeSprite(types[rand()%3], renderer);
	  pet->rect.x = x*48;
	  pet->rect.y = y*48;
	  break;
	}
      }
    }
  }
}

Sprite *Move(Sprite *a, Uint8 left, Uint8 right, Uint8 up, Uint8 down)
{
  SDL_Rect delta = {0,0,0,0};
  Sprite *b;

  if (left)  delta.x = -SPEED;
  if (right) delta.x = +SPEED;
  if (up)    delta.y = -SPEED;
  if (down)  delta.y = +SPEED;

  a->rect.x += delta.x;
  a->rect.y += delta.y;

  if ((b = CollidingWithAny(a))) {
    a->rect.x -= delta.x;
    a->rect.y -= delta.y;
  }

  return b;
}

void UpdateGame(void)
{
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);

  Move(player,
       keystate[SDL_SCANCODE_A], keystate[SDL_SCANCODE_D],
       keystate[SDL_SCANCODE_W], keystate[SDL_SCANCODE_S]);

  /*  switch (rand() % 60) {
  case 7:
    RandomPos(MakeSprite("dog1", NULL));
    break;
  case 11:
    RandomPos(MakeSprite("cat1", NULL));
    break;
  case 21:
    RandomPos(MakeSprite("sheep1", NULL));
    }*/
}
