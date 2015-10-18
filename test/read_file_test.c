/* Tested file */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "cutest/CuTest.h"

#include "../src/read_file.h"

#define TEST_FILE "./test/fs/file.in"
#define SAMPLE_INPUT "./test/fs/input.in"

void read_file_test(CuTest *tc) {
  int len = 5;
  char *test_input[] = {"this", "is", "a", "test", "file"};
  char **buffer = malloc(BUFF_LEN * sizeof(char*));
  read_config_file(buffer, TEST_FILE);
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

void parse_config_test(CuTest *tc) {
  char **buffer = malloc(BUFF_LEN * sizeof(char));
  read_config_file(buffer, SAMPLE_INPUT);
  /* struct Kv *config = parse_config(buffer); */
  free(buffer);
}


CuSuite* ReadFileGetSuite() {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, read_file_test);
  /* SUITE_ADD_TEST(suite, parse_config_test); */
  return suite;
}
