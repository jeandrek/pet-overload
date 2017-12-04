#include "overload.h"
#include <time.h>

Maze *MazeGen(void)
{
  Maze *maze = malloc(sizeof (Maze) * 10);

  maze[0] =  " ------------";
  maze[1] =  " ------------";
  maze[2] =  " ------------";
  maze[3] =  "      a   ---";
  maze[4] =  "--- ----- ---";
  maze[5] =  "--- ----- ---";
  maze[6] =  "--- ----- ---";
  maze[7] =  "---   a     e";
  maze[8] =  "-------------";
  maze[9] =  "-------------";

  return maze;
}

static const char *types[] = {"dog1", "cat1", "sheep1"};

void BuildMaze(Maze *maze, SDL_Renderer *renderer)
{
  srand(time(NULL));

  for (int y = 9; y > -1; y--) {
    for (int x = 0; x < 13; x++) {
      Sprite *sp;

      switch (maze[y][x]) {
      case '-':
	sp = MakeSprite("tree", renderer);
	sp->rect.x = x*48;
	sp->rect.y = y*48;
	sp->rect.x += (rand()%12)-6;
	sp->rect.y += (rand()%12)-6;
	break;
      case 'a':
	sp = MakeSprite(types[rand()%3], renderer);
	sp->rect.x = x*48;
	sp->rect.y = y*48;
	sp->data = 1<<31;
	break;
      case 'e':
	sp = MakeSprite("exit", renderer);
	sp->rect.x = x*48;
	sp->rect.y = y*48;
	break;
      }
    }
  }
}
