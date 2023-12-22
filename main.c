#include "barlist.h"
#include "defaults.h"
#include "colors.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

SDL_Window *window;
SDL_Renderer *renderer;

BarList *bars;

void Quit() {
  DestroyBarList(bars);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

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

  srand(time(NULL));

  int graphRightOffset = 40;
  int graphBottomY = 700;
  int numBars = 200;
  bars = CreateBarList();
  if (bars == NULL) {
    return -1;
  }

  for (int i = 0; i < numBars; i++) {
    int x = i * BAR_WIDTH + graphRightOffset;
    int value = rand() % 600;
    Bar *bar = CreateBar(x, graphBottomY, value);
    int added = AddToBarList(bars, *bar);

    free(bar);
    if (added < 0) {
      Quit();
    }
  }

  SDL_Event e;
  int running = 1;

  while (running) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        running = 0;
      }
    }

    SDL_SetRenderDrawColor(renderer, BG);
    SDL_RenderClear(renderer);

    for (long unsigned int i = 0; i < bars->size; i++) {
      DrawBar(renderer, bars->array[i]);
    }

    SDL_RenderPresent(renderer);
  }

  Quit();
  return 0;
}
