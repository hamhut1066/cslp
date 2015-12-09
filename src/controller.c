#include "controller.h"
#include "states.h"


void run_iteration(State *state) {
  state->time = state->time + 10000;
}

/*
 * This method sets up some basic things, then gets to work on the problem.
 */
void run_experiment(State *state) {
  State *initial_state = state;


  while (state->time < state->config->stop_time) {
    run_iteration(state);
  }
  print_state(initial_state);
}
