#include "bar.h"
#include "colors.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Could not initialize SDL2: %s\n", SDL_GetError());
    return -1;
  }

  SDL_Window *window =
      SDL_CreateWindow("CSorts", 0, 0, 1080, 720, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
    return -1;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  SDL_Event e;
  int running = 1;

  Bar* bar = CreateBar(200, 700, 300);

  while (running) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        running = 0;
      }
    }

    SDL_SetRenderDrawColor(renderer, BG);
    SDL_RenderClear(renderer);

    DrawBar(renderer, bar);

    SDL_RenderPresent(renderer);
  }

  DestroyBar(bar);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
