#include "../barlist.h"
#include <CUnit/CUnit.h>

void listInitCapacity() {
  BarList *list = CreateBarList();
  CU_ASSERT(list->capacity == 128);
  DestroyBarList(list);
}

void listInitSize() {
  BarList *list = CreateBarList();
  CU_ASSERT(list->size == 0);
  DestroyBarList(list);
}

void listCapacityWith1() {
  BarList *list = CreateBarList();
  Bar *bar = CreateBar(0, 0, 0);
  AddToBarList(list, *bar);
  CU_ASSERT(list->capacity == 128);
  DestroyBar(bar);
  DestroyBarList(list);
}

void listSizeWith1() {
  BarList *list = CreateBarList();
  Bar *bar = CreateBar(0, 0, 0);
  AddToBarList(list, *bar);
  CU_ASSERT(list->size == 1);
  DestroyBar(bar);
  DestroyBarList(list);
}

void listBarXAt1With1() {
  BarList *list = CreateBarList();
  Bar *bar = CreateBar(1, 2, 3);
  AddToBarList(list, *bar);
  CU_ASSERT(list->array[0].x == 1);
  DestroyBar(bar);
  DestroyBarList(list);
}

void listBarYAt1With1() {
  BarList *list = CreateBarList();
  Bar *bar = CreateBar(1, 2, 3);
  AddToBarList(list, *bar);
  CU_ASSERT(list->array[0].y == 2);
  DestroyBar(bar);
  DestroyBarList(list);
}

void listBarHAt1With1() {
  BarList *list = CreateBarList();
  Bar *bar = CreateBar(1, 2, 3);
  AddToBarList(list, *bar);
  CU_ASSERT(list->array[0].h == 3);
  DestroyBar(bar);
  DestroyBarList(list);
}

void listBarStatusAt1With1() {
  BarList *list = CreateBarList();
  Bar *bar = CreateBar(1, 2, 3);
  AddToBarList(list, *bar);
  CU_ASSERT(list->array[0].status == BAR_DEFAULT);
  DestroyBar(bar);
  DestroyBarList(list);
}
