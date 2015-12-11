#include "controller.h"
#include "states.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>

double uniform_deviate (int seed) {
  return seed * (1.0 / (RAND_MAX + 1.0));
}


/* char *format_time(int time) { */
/* } */
struct State *create_new_state(struct State *state) {
  return next_state(state);
}

/*
 * This method performs one tick, and returns the new state.
 */
struct State *tick(struct State *state) {
  double r;

  state = create_new_state(state);

  /* extract into sub-method */
  do
    r = uniform_deviate(rand());
  while (r == 0.0);

  int next_passenger = (int) (-log(r) * state->config->request_rate);

  state->time = state->time + next_passenger;

  return state;
}

/*
 * This method sets up some basic things, then gets to work on the problem.
 */
struct Stats *run_experiment(struct State *state) {
  struct Stats *stats = new_stats();
  // TODO: add an event printer to the project. This will make printing things easier.
  srand((int)time(NULL));
  rand(); /* calling once because first value is always the same */


  while (state->time < state->config->stop_time) {
    state = tick(state);
  }

  stats->state = state;
  return stats;
}
