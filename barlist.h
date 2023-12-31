#ifndef BARLIST_H
#define BARLIST_H

#include "bar.h"
#include <stdlib.h>

typedef struct BarList {
  Bar **array;
  size_t size;
  size_t capacity;
} BarList;

BarList *CreateBarList();
int AddToBarList(BarList *list, Bar *bar);
void DestroyBarList(BarList *list);

#endif // !BARLIST_H
