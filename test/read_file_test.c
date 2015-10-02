/* Tested file */
#include "CuTest.h"
#include <string.h>

#include "../src/read_file.h"

void read_file_test(CuTest *tc) {
 CuAssertStrEquals(tc, "b", "b");
 CuAssertStrEquals(tc, "a", "b");
}


CuSuite* ReadFileGetSuite() {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, read_file_test);
  return suite;
}
