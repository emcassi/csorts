#include "barlist_test.c"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

int main() {
  /* Initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  // BarList tests
  CU_pSuite barListSuite = CU_add_suite("Suite_1", NULL, NULL);
  if (barListSuite == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (CU_add_test(barListSuite, "test of listInitCapacity()",
                  listInitCapacity) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if (CU_add_test(barListSuite, "test of listInitSize()", listInitSize) ==
      NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if (CU_add_test(barListSuite, "test of listCapacityWith1()",
                  listCapacityWith1) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if (CU_add_test(barListSuite, "test of listSizeWith1()", listSizeWith1) ==
      NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if (CU_add_test(barListSuite, "test of listBarXAt1With1()",
                  listBarXAt1With1) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if (CU_add_test(barListSuite, "test of listBarYAt1With1()",
                  listBarYAt1With1) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if (CU_add_test(barListSuite, "test of listBarHAt1With1()",
                  listBarHAt1With1) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if (CU_add_test(barListSuite, "test of listBarStatusAt1With1()",
                  listBarStatusAt1With1) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
