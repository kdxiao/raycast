#ifndef MAP_H
#define MAP_H

typedef struct {
	int w, h;
	int **data;
} Map;

Map *init_map(void);
void cleanup_map(Map *map);
int map_get(Map *map, int x, int y);

#endif
