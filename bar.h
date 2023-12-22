#include <SDL2/SDL_render.h>

typedef struct Bar {
  int x;
  int y;
  int h;
  int status;
} Bar;

enum BarStatus {
  BAR_DEFAULT,
};

Bar* CreateBar(int x, int y, int h);
void DrawBar(SDL_Renderer *renderer, Bar *bar);
void DestroyBar(Bar *bar);
