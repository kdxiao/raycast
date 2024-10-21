#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <stdlib.h>
#include <SDL.h>
#include "player.h"
#include "map.h"

// As God intended.
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

#define FOV (90 * (M_PI / 180))
#define TILE_SIZE 8

typedef struct {
	float distance;
	float hit_X, hit_Y;
	int wall_type;
	int hit_side;
} Ray;

void cast_every_ray(Player *player, Map *map, SDL_Renderer *renderer);
Ray *cast_ray(Player *player, Map *map, float angle);

#endif
