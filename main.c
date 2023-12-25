#include "bar.h"
#include "barlist.h"
#include "colors.h"
#include "csorts.h"
#include "defaults.h"
#include "sorts.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
BarList *bars = NULL;

int sortDelay = SORT_DELAY;
int sortTimer = SORT_DELAY;

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Could not initialize SDL2: %s\n", SDL_GetError());
    return -1;
  }

  window = SDL_CreateWindow("CSorts", 0, 0, 1080, 720, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
    return -1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  srand(time(NULL));

  bars = CreateBarList();
  if (bars == NULL) {
    return -1;
  }

  for (int i = 0; i < numBars; i++) {
    int x = i * BAR_WIDTH + graphRightOffset;
    int value = rand() % maxBarHeight;
    Bar *bar = CreateBar(x, graphBottomY, value);
    int added = AddToBarList(bars, bar);

    if (added < 0) {
      free(bar);
      Quit();
    }
  }

  Uint64 now = SDL_GetPerformanceCounter();
  Uint64 last = 0;
  double deltaTime = 0;

  BubbleSetup bubbleSetup;
  BubbleInit(&bubbleSetup);

  SDL_Event e;
  int running = 1;
  int sortable = 1;
  int sorting = 0;

  while (running) {
    while (SDL_PollEvent(&e) != 0) {
      switch (e.type) {
      case SDL_KEYUP:
        switch (e.key.keysym.sym) {
        case SDLK_r:
          RandomizeBars(bars);
          bubbleSetup.complete = 0;
          BubbleInit(&bubbleSetup);
          sortable = 1;
          break;
        case SDLK_SPACE:
          if (sortable == 1) {
            sorting = 1 - sorting;
          }
          break;
        case SDLK_UP:
          sortDelay += sortTick;
          if (sortDelay > maxSortDelay) {
            sortDelay = maxSortDelay;
          }
          break;
        case SDLK_DOWN:
          sortDelay -= sortTick;
          if (sortDelay < minSortDelay) {
            sortDelay = minSortDelay;
          }
          break;
        }
        break;
      case SDL_QUIT:
        running = 0;
        break;
      }
    }

    last = now;
    now = SDL_GetPerformanceCounter();
    deltaTime =
        (double)(now - last) * 1000 / (double)SDL_GetPerformanceFrequency();

    if (sortable && sorting) {
      sortTimer -= deltaTime;
      if (sortTimer <= 0) {
        sortTimer = sortDelay;
        switch (BubbleStep(&bubbleSetup, bars)) {
        case -1:
          fprintf(stderr, "Failed bubble sort. Stopping now\n");
          sortable = 0;
          sorting = 0;
          break;
        case 0:
          if (bubbleSetup.b > 0) {
            bars->array[bubbleSetup.b - 1]->status = BAR_SELECTED;
            bars->array[bubbleSetup.b]->status = BAR_COMPARING;
          }
          break;
        case 1:
          fprintf(stdout, "Completed bubble sort\n");
          sorting = 0;
          sortable = 0;
          break;
        }
      }
    } else {
      sortTimer = 0;
    }

    SDL_SetRenderDrawColor(renderer, BG);
    SDL_RenderClear(renderer);

    for (unsigned long i = 0; i < bars->size; i++) {
      if (DrawBar(renderer, *bars->array[i]) < 0) {
        break;
      }
    }

    SDL_RenderPresent(renderer);
  }

  Quit();
  return 0;
}

void Quit() {
  DestroyBarList(bars);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void RandomizeBars(BarList *bars) {
  for (int i = 0; i < numBars; i++) {
    int value = rand() % maxBarHeight;
    bars->array[i]->h = value;
  }
}
