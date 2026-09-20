#ifndef PLAYER_H
#define PLAYER_H
#include <stdlib.h>
#include "map.h"

typedef struct {
	float x, y;  
	float theta; 
} Player;

Player *init_player(float x, float y, float theta);

#endif
