#include "controller.h"
#include "states.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>

double uniform_deviate (int seed) {
  return seed * (1.0 / (RAND_MAX + 1.0));
}

void run_iteration(State *state) {
  double r;

  do
    r = uniform_deviate(rand());
  while (r == 0.0);

  int next_passenger = (int) (-log(r)* state->config->request_rate);
  state->time = state->time + next_passenger;
}

/*
 * This method sets up some basic things, then gets to work on the problem.
 */
void run_experiment(State *state) {
  srand((int)time(NULL));
  rand(); /* calling once because first value is always the same */


  while (state->time < state->config->stop_time) {
    run_iteration(state);
  }
}
