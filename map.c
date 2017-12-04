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

  map[0] = malloc(16); map[1] = malloc(16);
  map[2] = malloc(16); map[3] = malloc(16);
  map[4] = malloc(16); map[5] = malloc(16);
  map[6] = malloc(16); map[7] = malloc(16);
  map[8] = malloc(16); map[9] = malloc(16);
  map[10] = malloc(7);

  fgets(map[0], 16, f); fgets(map[1], 16, f);
  fgets(map[2], 16, f); fgets(map[3], 16, f);
  fgets(map[4], 16, f); fgets(map[5], 16, f);
  fgets(map[6], 16, f); fgets(map[7], 16, f);
  fgets(map[8], 16, f); fgets(map[9], 16, f);
  fgets(map[10], 7, f);

  return map;
}

static const char *types[] = {"dog1", "cat1", "sheep1"};

void BuildMap(Map *map, SDL_Renderer *renderer)
{
  srand(time(NULL));

  for (int y = MAP_HEIGHT-1; y > -1; y--) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      Sprite *sp;

      switch (map[y][x]) {
      case '-':
	sp = MakeSprite("tree", renderer);
	sp->rect.x = x*48 + (rand()%12)-6;
	sp->rect.y = y*48 + (rand()%12)-6;
	break;
      case '1':
	sp = MakeSprite("brick1", renderer);
	sp->rect.x = x*48;
	sp->rect.y = y*48;
	break;
      case '2':
	sp = MakeSprite("brick2", renderer);
	sp->rect.x = x*48;
	sp->rect.y = y*48;
	break;
      case '3': case '4': case '5':
	{
	  char name[8] = "brickn";
	  name[5] = map[y][x];
	  sp = MakeSprite(name, renderer);
	  sp->rect.x = x*48;
	  sp->rect.y = y*48;
	  break;
	}
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
