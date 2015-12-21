#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "cutest/CuTest.h"

#include "../src/controller.h"
#include "../src/read_file.h"

/* generates a state with the default test file */
struct State *test_state() {
  struct Config config;

  read_config_file(&config, "./test/fs/input.in");

  return get_state(&config);
}

/*
 * tests the initial state of the state is correct.
 */
void initial_iteration_test(CuTest *tc) {
  struct State *state = test_state();

  /* test that the initial state is correctly configured */
  CuAssertIntEquals(tc, 0, state->no);
  CuAssertIntEquals(tc, 0, state->time);
  CuAssertIntEquals(tc, 86400, state->config->stop_time);

  /* test that the buses are located in the initial position */
  CuAssertIntEquals(tc, 0, state->buses->no);
  CuAssertIntEquals(tc, 0, state->buses->location->no);


  struct Bus *bus = state->buses;
  bus += 4;

  /*
   * test that consecutive buses are in the proper location
   * and have the correct id.
   */
  CuAssertIntEquals(tc, 4, bus->no);
  CuAssertIntEquals(tc, 0, bus->location->no);

  /*
   * test that the stops are initialised correctly
   * this tests all stops and that their numbers are correctly assigned.
   */
  CuAssertIntEquals(tc, 0, state->stops->no);

  int i;
  for (i = 0; i < state->config->no_stops; i++) {
    CuAssertIntEquals(tc, i, (state->stops + i)->no);
  }

  /*
   * This tests the stop edges are correctly assigned.
   * this is not a blanket test, but a sampling of edges.
   */
  CuAssertIntEquals(tc, 2, state->stops->adjacent);
  CuAssertIntEquals(tc, 3, state->stops->edges->weight);
}

/*
 * Test state at the end of the experiment.
 */
void end_of_experiment_test(CuTest *tc) {
  struct State *state = test_state();
  struct Stats *stats;

  stats = run_experiment(state);

  /*
   * test that the end-state's time is greater than the configured running time.
   * this also tests that the states have been incremented to above 0.
   * this is to check that states are transitioning properly.
   */
  CuAssertIntEquals(tc, 1, stats->state->time >= stats->state->config->stop_time);
  CuAssertIntEquals(tc, 1, stats->state->no >= 1);
}

/*
 * Testing one tick of the program.
 */
void tick_increments_state(CuTest *tc) {
  struct State *state = test_state();
  struct State *original_state = state;
  /*
   * remember that the seed is not random!!
   * This gives us a predictable testing environment.
   */
  srand(1337);

  state = tick(state);

  /*
   * check that the previous state is referenced from the new state.
   * check that the original state does not equal the new state struct.
   */
  CuAssertPtrEquals(tc, original_state, state->last);
  CuAssertIntEquals(tc, 0, original_state == state);

  /*
   * check that the state no. has incremented correctly.
   */
  CuAssertIntEquals(tc, 1, state->no);
  CuAssertIntEquals(tc, 0, original_state->no);

  /*
   * check that the time of the second event is greater than the time of the initial event
   * check that the time is greater than 0.
   */
  CuAssertIntEquals(tc, 1, state->time > original_state->time);
  CuAssertIntEquals(tc, 1, state->time > 0);

  destroy_state(state);
}

/*
 * Test that I am formatting time output correctly
 * formats an int representing time (seconds), returns a representation in string format.
 */
void test_format_time(CuTest *tc) {
  CuAssertStrEquals(tc, "01:00:00:00", format_time(86400));
  CuAssertStrEquals(tc, "00:00:00:00", format_time(0));
  CuAssertStrEquals(tc, "00:00:00:59", format_time(59));
  CuAssertStrEquals(tc, "00:00:01:01", format_time(61));
}

/*
 * Test the shortest route. (not fully implemented...)
 */
void test_shortest_route(CuTest *tc) {
  struct State *state = test_state();

  shortest_route(state, 0, 4);
}

/*
 * test the minimum vertex from the input vertex.
 */
void test_min_vertex(CuTest *tc) {
  int length = 10;
  int *vertex = malloc(length * sizeof(int));
  int *dist = malloc(length * sizeof(int));

  /* initialise the arrays to available and 'infinite' distance */
  for (int i = 0; i < length; i++) {
    vertex[i] = 1;
    dist[i] = INT_MAX;
  }

  dist[0] = 0;

  /* test that the correct vertices are returned */
  CuAssertIntEquals(tc, 0, min_vertex(vertex, dist, length));

  vertex[0] = 0;
  CuAssertIntEquals(tc, 1, min_vertex(vertex, dist, length));

  vertex[1] = 0;
  dist[3] = 12;
  CuAssertIntEquals(tc, 3, min_vertex(vertex, dist, length));
}

/*
 * check if two stops in a stop system are adjacent or not.
 */
void test_stop_adjacent(CuTest *tc) {
  struct State *state = test_state();

  /* the same stop cannot be adjacent to itself */
  CuAssertIntEquals(tc, -1, stop_adjacent(state, 0, 0));
  CuAssertIntEquals(tc, 0, stop_adjacent(state, 0, 1));
  CuAssertIntEquals(tc, -1, stop_adjacent(state, 2, 0));
  CuAssertIntEquals(tc, 1, stop_adjacent(state, 0, 5));
}

/*
 * Test-Suite collector
 */
CuSuite* ControllerGetSuite(void) {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, initial_iteration_test);
  SUITE_ADD_TEST(suite, end_of_experiment_test);
  SUITE_ADD_TEST(suite, tick_increments_state);
  SUITE_ADD_TEST(suite, test_format_time);
  SUITE_ADD_TEST(suite, test_shortest_route);
  SUITE_ADD_TEST(suite, test_min_vertex);
  SUITE_ADD_TEST(suite, test_stop_adjacent);
  return suite;
}
