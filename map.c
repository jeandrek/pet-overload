#include "overload.h"
#include <time.h>

Map *LoadMap(const char *name)
{
  Map *map = malloc(sizeof (Map) * 11);
  char path[32];
  FILE *f;

  snprintf(path, 32, "assets/%s.map", name);
#ifdef DEBUG
  fprintf(stderr, "Debug: loading file %s\n", path);
#endif
  if ((f = fopen(path, "r")) == NULL) {
    perror("Error");
    exit(EXIT_FAILURE);
  }

  map[0] = malloc(15); map[1] = malloc(15);
  map[2] = malloc(15); map[3] = malloc(15);
  map[4] = malloc(15); map[5] = malloc(15);
  map[6] = malloc(15); map[7] = malloc(15);
  map[8] = malloc(15); map[9] = malloc(15);
  map[10] = malloc(7);

  fgets(map[0], 15, f); fgets(map[1], 15, f);
  fgets(map[2], 15, f); fgets(map[3], 15, f);
  fgets(map[4], 15, f); fgets(map[5], 15, f);
  fgets(map[6], 15, f); fgets(map[7], 15, f);
  fgets(map[8], 15, f); fgets(map[9], 15, f);
  fgets(map[10], 7, f);

  return map;
}

static const char *types[] = {"dog1", "cat1", "sheep1"};

void BuildMap(Map *map, SDL_Renderer *renderer)
{
  srand(time(NULL));

  for (int y = 9; y > -1; y--) {
    for (int x = 0; x < 13; x++) {
      Sprite *sp;

      switch (map[y][x]) {
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
	sp->data = MASK_ANIMAL;
	break;
      case 'n':
	sp = MakeSprite("npc", renderer);
	sp->rect.x = x*48;
	sp->rect.y = y*48;
	sp->data = MASK_NPC;
	break;
      case 'e':
	sp = MakeSprite("exit", renderer);
	sp->rect.x = x*48;
	sp->rect.y = y*48;
	sp->data = MASK_EXIT;
	break;
      }
    }
  }
}
