#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "cutest/CuTest.h"

#include "../src/controller.h"
#include "../src/read_file.h"

/* generates a state with the default test file */
struct State *test_state() {
  struct Config config;

  read_config_file(&config, "./test/fs/input.in");

  return get_state(&config);
}


void initial_iteration_test(CuTest *tc) {
  struct State *state = test_state();

  CuAssertIntEquals(tc, 0, state->no);
  CuAssertIntEquals(tc, 0, state->time);
  CuAssertIntEquals(tc, 86400, state->config->stop_time);
}


void end_of_experiment_test(CuTest *tc) {
  struct State *state = test_state();
  struct Stats *stats;

  stats = run_experiment(state);

  CuAssertIntEquals(tc, 1, stats->state->time >= stats->state->config->stop_time);
  CuAssertIntEquals(tc, 1, stats->state->no >= 1);
}

void tick_increments_state(CuTest *tc) {
  struct State *state = test_state();
  struct State *original_state = state;

  state = tick(state);

  CuAssertPtrEquals(tc, original_state, state->last);
  CuAssertIntEquals(tc, 1, state->no);
  CuAssertIntEquals(tc, 0, original_state->no);

  destroy_state(state);
}

CuSuite* ControllerGetSuite(void) {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, initial_iteration_test);
  SUITE_ADD_TEST(suite, end_of_experiment_test);
  SUITE_ADD_TEST(suite, initial_iteration_test);
  SUITE_ADD_TEST(suite, tick_increments_state);
  return suite;
}
