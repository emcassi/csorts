#include "bar.h"
#include "colors.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdlib.h>

Bar *CreateBar(int x, int y, int h) {
  Bar *bar = (Bar *)malloc(sizeof(Bar));
  bar->x = x;
  bar->y = y;
  bar->h = h;
  return bar;
}

void DrawBar(SDL_Renderer *renderer, Bar *bar) {
  SDL_Rect rect = {bar->x, bar->y - bar->h, 20, bar->h};

  switch (bar->status) {
  case BAR_DEFAULT:
    SDL_SetRenderDrawColor(renderer, WHITE);
  }
  SDL_RenderFillRect(renderer, &rect);
}

void DestroyBar(Bar *bar) { free(bar); }