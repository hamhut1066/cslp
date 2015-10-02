/* Tested file */
#include "CuTest.h"
#include <string.h>

#include "../src/read_file.h"

void read_file_test(CuTest *tc) {
  char *test_input[] = {"this", "is", "a", "test", "file"};
  char **buffer = read_config_file("./test/fs/file.in");
  int i = 0;
  while (buffer[i] != '\0') {
    CuAssertStrEquals(tc, test_input[i], buffer[i]);
    i++;
  }
  // free(buffer);
}


CuSuite* ReadFileGetSuite() {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, read_file_test);
  return suite;
}
