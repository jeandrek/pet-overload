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
  maze[7] =  "---   a      ";
  maze[8] =  "-------------";
  maze[9] =  "-------------";

  return maze;
}

void BuildMaze(Maze *maze, SDL_Renderer *renderer)
{
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
