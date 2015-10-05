/* Tested file */
#include "CuTest.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/read_file.h"

#define BUFF_LEN 50
void read_file_test(CuTest *tc) {
  int len = 5;
  char *test_input[] = {"this", "is", "a", "test", "file"};
  char **buffer = malloc(BUFF_LEN * sizeof(char*));
  read_config_file(buffer, "./test/fs/file.in");
  int i = 0;
  while (i < len) {
    CuAssertStrEquals(tc, test_input[i], buffer[i]);
    i++;
  }
  for(i = 0; buffer[i]; i++) {
    free(buffer[i]);
  }
  free(buffer);
}


CuSuite* ReadFileGetSuite() {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, read_file_test);
  return suite;
}
