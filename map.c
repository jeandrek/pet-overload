#include "overload.h"
#include <time.h>

Map *LoadMap(const char *name)
{
  Map *map = malloc(sizeof (Map) * 11);
  char path[128];
  FILE *f;

  snprintf(path, 128, "%s/%s.map", assetspath, name);
#ifdef DEBUG
  fprintf(stderr, "Debug: loading file %s\n", path);
#endif
  if ((f = fopen(path, "r")) == NULL) {
    perror("Error");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 10; i++)
    map[i] = fgets(malloc(16), 16, f);
  map[10] = fgets(malloc(7), 7, f);

  return map;
}

void FreeMap(Map *map)
{
  for (int i = 0; i < 10; i++)
    free(map[i]);
  free(map);
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
      case '1': case '2': case '3': case '4': case '5':
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
      case 'g':
	sp = MakeSprite("gate1", renderer);
	sp->rect.x = x*48;
	sp->rect.y = y*48;
	sp->data = MASK_GATE;
	break;
      }
    }
  }
}
