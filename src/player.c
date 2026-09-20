#include <stdio.h>
#include <SDL.h>
#include <math.h>
#include <stdlib.h>
#include "player.h"
#include "map.h"

#define MOVE_SPEED 1
#define ROT_SPEED 1
#define FOV 60

Player *init_player(float x, float y, float theta) {
	Player *player = malloc(sizeof(Player));
	if (!player) return NULL;

	player->x = x;
	player->y = y;
	player->theta = theta;
	return player;
}


