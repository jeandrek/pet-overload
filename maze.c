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
