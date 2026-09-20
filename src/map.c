#include <stdio.h>
#include <stdlib.h>
#include "map.h"

#define MAP_WIDTH 16
#define MAP_HEIGHT 12

Map *init_map(void) {
	Map *map = malloc(sizeof(Map));
	if (!map) return NULL;

	map->w = MAP_WIDTH;
	map->h = MAP_HEIGHT;
	map->data = malloc(map->h * sizeof(int*));

	if (!map->data) {
		free(map);
		return NULL;
	}

	for (int y = 0; y < map->h; y++) {
		map->data[y] = malloc(map->w* sizeof(int));
		if (!map->data[y]) {
			for (int i = 0; i < y; i++) {
				free(map->data[i]);
			}
			free(map->data);
			free(map);
			return NULL;
		}
	}

	int default_map[MAP_HEIGHT][MAP_WIDTH] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}		
	};

	for (int y = 0; y < map->h; y++) {
		for (int x = 0; x < map->w; x++) {
			map->data[y][x] = default_map[y][x];
		}
	}

	return map;
}

void cleanup_map(Map *map) {
	if (!map) return;
	if (map->data) {
		for (int i = 0; i < map->h; i++) {
			free(map->data[i]);
		}
		free(map->data);
	}
	free(map);
}

int map_get(Map *map, int x, int y) {
	if (!map) return -1;
	if (x < 0 || y < 0 || x >= map->w || y >= map->h) {
		return -1;
	}
	return map->data[y][x];
}
