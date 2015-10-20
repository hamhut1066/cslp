/* Tested file */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "cutest/CuTest.h"

#include "../src/read_file.h"

#define TEST_FILE "./test/fs/file.in"
#define SAMPLE_INPUT "./test/fs/input.in"


void parse_config_test(CuTest *tc) {
  config_t config;
  State *state = state_initial_state();

  if (!read_config_file(&config, SAMPLE_INPUT)) {
    printf("There was an issue with the config file %s\n", SAMPLE_INPUT);
  }

  parse_config(state, &config);
  print_state(state);

  config_destroy(&config);
  destroy_state(state);

}


CuSuite* ReadFileGetSuite() {
  CuSuite* suite = CuSuiteNew();
  /* SUITE_ADD_TEST(suite, read_file_test); */
  SUITE_ADD_TEST(suite, parse_config_test);
  return suite;
}
