#ifndef CSORTS_H
#define CSORTS_H

#include "barlist.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern BarList *bars;

const int graphRightOffset = 40;
const int graphBottomY = 710;
const int numBars = 200;
const int maxBarHeight = 700;

void Quit();
void RandomizeBars(BarList *bars);

#endif // CSORTS_H
