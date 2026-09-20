#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <math.h>
#include "map.h"
#include "player.h"
#include "raycaster.h"

float dist(int x1, int y1, int x2, int y2) {
	return sqrt((x2-x1) * (x2-x1) + (y2-y1) * (y2-y1));
}

void render_ray() {
	return;
}

void cast_every_ray(Player *player, Map *map, SDL_Renderer *renderer) {
	float first_angle = player->theta - (FOV / 2);
	float angle_step = FOV / SCREEN_WIDTH;
	printf("Casting rays.\n");
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	int hwh = 0;
	float cur_angle = first_angle;
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		printf("Casting Ray %d\n", i);
		Ray* cur_ray = cast_ray(player, map, cur_angle);

		if (cur_ray->wall_type == 1) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
		}

		hwh = cosf(fabs(player->theta - cur_angle)) != 0 ? 1536.0f / (cosf(fabs(player->theta - cur_angle)) * cur_ray->distance) : INFINITY;
		printf("%d\n", hwh);
		SDL_RenderDrawLine(renderer, i, SCREEN_HEIGHT / 2 - hwh,
									 i, SCREEN_HEIGHT / 2 + hwh);

		cur_angle += angle_step;
	}
	SDL_RenderPresent(renderer);
}

Ray *cast_ray(Player *player, Map *map, float angle) {
	Ray *ray = malloc(sizeof(Ray));
	printf("a\n");
	float dx_1 = tan(angle) != 0 ? TILE_SIZE * (1 - fmod(player->y, TILE_SIZE) / TILE_SIZE) / tan(angle) : INFINITY;
	float dx = tan(angle) != 0 ? TILE_SIZE / tan(angle) : INFINITY;
	printf("b\n");
	float dy_1 = TILE_SIZE * (1 - fmod(player->x, TILE_SIZE) / TILE_SIZE) * tan(angle);
	float dy = TILE_SIZE * tan(angle); 
	printf("c\n");

	float cur_x = player->x + dx_1;
	float cur_y = player->y + dy_1;
	printf("d\n");

	int y_steps;
	int x_steps;
	printf("e\n");

	for (x_steps = 0; x_steps < map->w; x_steps++) {
		printf("X Step %d\n", x_steps);
		int cur_tile_x = x_steps + (int) player->x / TILE_SIZE + 1;
		int cur_tile_y = cur_y / TILE_SIZE;
		if (cur_tile_x >= map->w) {
			break;
		}
		if (cur_tile_y >= map->h) {
			break;
		}
		if (map->data[cur_tile_y][cur_tile_x] > 0) {
			break;
		}	
		cur_y += dy;	
	}
	for (y_steps = 0; y_steps < map->h; y_steps++) {
		printf("Y Step %d\n", y_steps);
		int cur_tile_x = cur_x / TILE_SIZE;
        int cur_tile_y = y_steps + (int) player->y / TILE_SIZE + 1;
		if (cur_tile_x >= map->w) {
			break;
		}
		if (cur_tile_y >= map->h) {
			break;
		}
		if (map->data[cur_tile_y][cur_tile_x] > 0) {
			break;
		}	
		cur_x += dx;
	}
	printf("f\n");

	float dist_vert = dist(player->x, player->y,
						   TILE_SIZE * ((int) player->x / TILE_SIZE + x_steps + 1), cur_y);
	printf("g\n");
	float dist_hori = dist(player->x, player->y,
					       cur_x, TILE_SIZE * ((int) player->y / TILE_SIZE + y_steps + 1));
	printf("h\n");
	if (dist_vert < dist_hori) {
		ray->distance = dist_vert;
		ray->hit_X = TILE_SIZE * ((int) player->x / TILE_SIZE + x_steps + 1);
		ray->hit_Y = cur_y;
		ray->wall_type = 1;
	}
	else {
		ray->distance = dist_hori;
		ray->hit_X = cur_x;
		ray->hit_Y = TILE_SIZE * ((int) player->y / TILE_SIZE + y_steps + 1);
		ray->wall_type = 2;
	}
	return ray;
}
