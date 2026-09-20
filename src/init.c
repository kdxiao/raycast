#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

bool init_SDL(SDL_Window **window, SDL_Renderer **renderer, int width, int height) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize. Error code: %s\n", SDL_GetError());
		return false;
	}

	*window = SDL_CreateWindow("raycaster :3",
							    SDL_WINDOWPOS_CENTERED,
							    SDL_WINDOWPOS_CENTERED,
								width, 
								height,
								SDL_WINDOW_RESIZABLE);

	if (*window == NULL) {
		printf("Window could not be created. Error code: %s\n", SDL_GetError());
		SDL_Quit();
		return false;
	}
	printf("Window created.\n");

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

	if (*renderer == NULL) {
		printf("Renderer could not be created. Error code: %s\n", SDL_GetError());
		SDL_DestroyWindow(*window);
		SDL_Quit();
		return false;
	}
	printf("Renderer created.\n");

	SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255);
	return true;
}

void kill_SDL(SDL_Window *window, SDL_Renderer *renderer) {
	if (renderer != NULL) {
		SDL_DestroyRenderer(renderer);
	}
	if (window != NULL) {
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
}
