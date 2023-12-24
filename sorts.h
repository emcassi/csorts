#include "barlist.h"

typedef struct BubbleSetup {
  unsigned int a, b, swapped, inLoop, complete;
} BubbleSetup;

void BubbleStep(BubbleSetup *setup, BarList *list);
