#include <stdio.h>
#include <SDL.h>
#include <math.h>
#include "init.h"
#include "player.h"
#include "map.h"
#include "raycaster.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
// #define PI 3.14159265

int main(int argc, char *argv[]) {
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	// Initialize SDL
	if (!init_SDL(&window, &renderer, SCREEN_WIDTH, SCREEN_HEIGHT)) {
		printf("SDL could not initialize\n");
		return 1;
	}

	// Init to middle of first non-wall block, angled at 0.2 rads
	Player *player = init_player(TILE_SIZE * 3 / 2, TILE_SIZE * 3 /2, 0.3f); 
	Map *map = init_map();

	SDL_Event e;
	bool quit = false;
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	cast_every_ray(player, map, renderer);
	while (!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_KEYDOWN){
				quit = true;
			}
		}
	}

	kill_SDL(window, renderer);
	return 0;
}