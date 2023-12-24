#include "barlist.h"

typedef struct BubbleSetup {
  unsigned int a, b, swapped, inLoop, complete;
} BubbleSetup;

void BubbleInit(BubbleSetup *setup);
int BubbleStep(BubbleSetup *setup, BarList *list);
