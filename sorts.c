#include "sorts.h"

void BubbleStep(BubbleSetup *setup, BarList *list) {
  if (setup->complete == 1) {
    return;
  }

  if (setup->inLoop == 1) {
    if (setup->b < list->size - setup->a - 1) {
      if (list->array[setup->b].h > list->array[setup->a].h) {
        // Swap
        int temp = list->array[setup->b].h;
        list->array[setup->b].h = list->array[setup->a].h;
        list->array[setup->a].h = temp;
        setup->swapped = 1;
      }

      setup->b++;
    } else {
      if (setup->swapped == 0) {
        setup->complete = 1;
        return;
      }
      setup->inLoop = 0;
    }
  } else {
    if (setup->a < list->size) {
      setup->inLoop = 1;
      setup->a++;
      setup->b = 0;
    } else {
      setup->complete = 1;
    }
  }
}
