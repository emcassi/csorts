#include "barlist.h"
#include "defaults.h"
#include <stdio.h>
#include <stdlib.h>

BarList *CreateBarList() {
  BarList *list = malloc(sizeof(BarList));
  if (list == NULL) {
    fprintf(stderr, "Unable to create BarList\n");
    return NULL;
  }

  list->capacity = INITIAL_BARLIST_CAPACITY;
  list->array = (Bar *)malloc(sizeof(Bar) * list->capacity);
  if (list->array == NULL) {
    fprintf(stderr, "Unable to create BarList array\n");
    free(list);
    return NULL;
  }
  list->size = 0;

  return list;
}

int AddToBarList(BarList *list, Bar bar) {
  // Increase Capacity if necessary
  if (list->size == list->capacity) {
    if (list->capacity == MAX_BARLIST_CAPACITY) {
      fprintf(stderr, "Can't increase Bars capacity: Too many bars!\n");
      return -1;
    }

    size_t newCapacity = list->capacity * 2;
    if (newCapacity > MAX_BARLIST_CAPACITY) {
      fprintf(stderr, "Can't increase Bars capacity\n");
      return -1;
    }

    Bar *temp = realloc(list->array, sizeof(Bar) * newCapacity);
    if (temp == NULL) {
      fprintf(stderr, "Can't increase Bars Capacity\n");
      return -1;
    }

    list->array = temp;
    list->capacity = newCapacity;
  }

  list->size++;
  list->array[list->size - 1] = bar;
  return 0;
}

int RemoveFromBarList(BarList *list, size_t index) {
  if (list->size == 0) {
    fprintf(stderr, "Can't remove that element from BarList: List is empty\n");
    return -1;
  }

  if (index >= list->size) {
    fprintf(stderr,
            "Can't remove that element from BarList: Index doesn't exist\n");
    return -1;
  }

  for (size_t i = index; i < list->size - 1; i++) {
    list->array[i] = list->array[i + 1];
  }

  list->size--;
  return 0;
}

void DestroyBarList(BarList *list) {
  if (list != NULL) {
    free(list->array);
    free(list);
  }
}
