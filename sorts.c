#include "sorts.h"
#include "bar.h"

void BubbleInit(BubbleSetup *setup) {
  setup->a = 0;
  setup->b = 0;
  setup->inLoop = 0;
  setup->swapped = 0;
  setup->complete = 0;
}

int BubbleStep(BubbleSetup *setup, BarList *list) {
  if (setup->complete == 1) {
    return 1;
  }

  // Main loop control
  if (setup->inLoop == 1) {
    // Ensure we don't go out of bounds
    if (setup->b < list->size - setup->a - 1) {
      // Additional NULL checks for safety
      if (list->array[setup->b] == NULL || list->array[setup->b + 1] == NULL) {
        fprintf(stderr, "Missing bar\n");
        return -1;
      }

      // Compare heights and swap if necessary
      if (list->array[setup->b]->h > list->array[setup->b + 1]->h) {
        // Swap
        int temp = list->array[setup->b]->h;
        list->array[setup->b]->h = list->array[setup->b + 1]->h;
        list->array[setup->b + 1]->h = temp;
        setup->swapped = 1;
      }
      // Move to next pair
      setup->b++;
    } else {
      // Reset loop control if end of one pass through the array
      if (setup->swapped == 0) {
        setup->complete = 1;
      }
      setup->inLoop = 0;
      setup->a++;
    }
  } else {
    // Prepare for the next iteration
    if (setup->a < list->size - 1) {
      setup->inLoop = 1;
      setup->b = 0;
    } else {
      // Reset everything if the end of array is reached
      setup->a = 0;
      setup->b = 0;
      setup->inLoop = 0;
      setup->complete = 1;
    }
  }

  return 0;
}
