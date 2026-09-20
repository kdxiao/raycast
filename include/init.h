#ifndef INIT_H
#define INIT_H

#include <SDL.h>
#include <stdbool.h>

bool init_SDL(SDL_Window **window, SDL_Renderer **renderer, int weight, int height);
void kill_SDL(SDL_Window *window, SDL_Renderer *renderer);

#endif
