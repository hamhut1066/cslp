/* Tested file */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "cutest/CuTest.h"

#include "../src/read_file.h"

#define SAMPLE_INPUT "./test/fs/input.in"
#define BAD_INPUT  "./test/fs/bad_config_file.in"


void parse_config_test(CuTest *tc) {
  State *state = get_initial_state();
  struct Config *config = get_initial_config();

  read_config_file(config, SAMPLE_INPUT);
  set_initial_state(state, config);

  CuAssertIntEquals(tc, config->bus_capacity, state->config->bus_capacity);
  CuAssertIntEquals(tc, config->bus_capacity, 12);

  CuAssertIntEquals(tc, config->map[0][0], 0);
  CuAssertIntEquals(tc, config->map[1][2], 5);
  CuAssertIntEquals(tc, config->map[3][2], -1);

  destroy_config(config);
  destroy_state(state);

}

void parse_bad_config_test(CuTest *tc) {
  struct Config *config = get_initial_config();

  read_config_file(config, BAD_INPUT);

  CuAssertIntEquals(tc, config->bus_capacity, 12);

  CuAssertIntEquals(tc, config->map[0][0], 0);
  CuAssertIntEquals(tc, config->map[1][2], 5);
  CuAssertIntEquals(tc, config->map[3][2], -1);


  destroy_config(config);
}


CuSuite* ReadFileGetSuite() {
  CuSuite* suite = CuSuiteNew();
  /* SUITE_ADD_TEST(suite, read_file_test); */
  SUITE_ADD_TEST(suite, parse_config_test);
  SUITE_ADD_TEST(suite, parse_bad_config_test);
  return suite;
}
