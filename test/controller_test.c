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
  // struct Bus *null_bus = NULL;

  CuAssertIntEquals(tc, 0, state->no);
  CuAssertIntEquals(tc, 0, state->time);
  CuAssertIntEquals(tc, 86400, state->config->stop_time);

  /* test buses */
  CuAssertIntEquals(tc, 0, state->buses->no);
  CuAssertIntEquals(tc, 0, state->buses->location->no);


  struct Bus *bus = state->buses;
  bus += 4;

  CuAssertIntEquals(tc, 4, bus->no);
  CuAssertIntEquals(tc, 0, bus->location->no);

  /* test locations */
  CuAssertIntEquals(tc, 0, state->stops->no);

  int i;
  for (i = 0; i < state->config->no_stops; i++) {
    CuAssertIntEquals(tc, i, (state->stops + i)->no);
  }

  /* test stop edges */
  CuAssertIntEquals(tc, 2, state->stops->adjacent);
  CuAssertIntEquals(tc, 3, state->stops->edges->weight);
}


void end_of_experiment_test(CuTest *tc) {
  struct State *state = test_state();
  struct Stats *stats;

  stats = run_experiment(state);

  CuAssertIntEquals(tc, 1, stats->state->time >= stats->state->config->stop_time);
  CuAssertIntEquals(tc, 1, stats->state->no >= 1);
}

/*
 * remember that the seed is not random!!
 */
void tick_increments_state(CuTest *tc) {
  struct State *state = test_state();
  struct State *original_state = state;
  srand(1337);

  state = tick(state);

  CuAssertPtrEquals(tc, original_state, state->last);
  CuAssertIntEquals(tc, 0, original_state == state);

  CuAssertIntEquals(tc, 1, state->no);
  CuAssertIntEquals(tc, 0, original_state->no);

  CuAssertIntEquals(tc, 1, state->time > original_state->time);
  CuAssertIntEquals(tc, 1, state->time > 0);

  destroy_state(state);
}

/*
 * Test that I am formatting time output correctly
 */
void test_format_time(CuTest *tc) {
  CuAssertStrEquals(tc, "01:00:00:00", format_time(86400));
  CuAssertStrEquals(tc, "00:00:00:00", format_time(0));
  CuAssertStrEquals(tc, "00:00:00:59", format_time(59));
  CuAssertStrEquals(tc, "00:00:01:01", format_time(61));
}

CuSuite* ControllerGetSuite(void) {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, initial_iteration_test);
  SUITE_ADD_TEST(suite, end_of_experiment_test);
  SUITE_ADD_TEST(suite, tick_increments_state);
  SUITE_ADD_TEST(suite, test_format_time);
  return suite;
}
