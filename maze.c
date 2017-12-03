#include "overload.h"
#include <time.h>

Maze *MazeGen(void)
{
  Maze *maze = malloc(2 * 10);

  maze[0] = 0b0111111111111;
  maze[1] = 0b0111111111111;
  maze[2] = 0b0111111111111;
  maze[3] = 0b0000000000111;
  maze[4] = 0b1110111110111;
  maze[5] = 0b1110111110111;
  maze[5] = 0b1110111110111;
  maze[6] = 0b1110111110111;
  maze[7] = 0b1110000000000;
  maze[8] = 0b1111111111111;
  maze[9] = 0b1111111111111;

  return maze;
}
