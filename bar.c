#include "bar.h"
#include "colors.h"
#include "defaults.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdlib.h>

Bar *CreateBar(int x, int y, int h) {
  Bar *bar = (Bar *)malloc(sizeof(Bar));
  bar->x = x;
  bar->y = y;
  bar->h = h;
  bar->status = BAR_DEFAULT;
  return bar;
}

int DrawBar(SDL_Renderer *renderer, Bar bar) {
  if (renderer == NULL) {
    fprintf(stderr, "Invalid renderer\n");
    return -1;
  }
  SDL_Rect rect = {bar.x, bar.y - bar.h, BAR_WIDTH, bar.h};

  switch (bar.status) {
  case BAR_DEFAULT:
    SDL_SetRenderDrawColor(renderer, WHITE);
    break;
  case BAR_SELECTED:
    SDL_SetRenderDrawColor(renderer, GREEN);
    break;
  case BAR_COMPARING:
    SDL_SetRenderDrawColor(renderer, RED);
    break;
  }
  if (SDL_RenderFillRect(renderer, &rect) < 0) {
    fprintf(stderr, "Failed to draw bar: %s\n", SDL_GetError());
    return -1;
  }
  return 0;
}

void DestroyBar(Bar *bar) { free(bar); }
