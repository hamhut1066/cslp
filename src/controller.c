#include "controller.h"
#include "states.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <limits.h>

#define DAY_SECS 86400
#define HOUR_SECS 3600
#define MIN_SECS 60
#define TIME_SIZE 12

/*
 * generating uniformly distributed events
 */
double uniform_deviate (int seed) {
  return seed * (1.0 / (RAND_MAX + 1.0));
}

double random_value(double request_rate, double modulo) {
  double r;
  do
    r = uniform_deviate(rand());
  while (r == 0.0);

  r = (-log(r) * request_rate);
  if (modulo == 0.0) {
    return r;
  } else {
    return fmod(r, modulo);
  }
}

/*
 * formats the time to be beautiful
 */
char *format_time(int time) {
  char *formatted_time = malloc(TIME_SIZE * sizeof(char));

  int days = time / DAY_SECS; /* seconds in a day */
  int hours = (time % DAY_SECS) / HOUR_SECS;
  int mins = ((time % DAY_SECS) % HOUR_SECS) / MIN_SECS;
  int secs = ((time % DAY_SECS) % HOUR_SECS) % MIN_SECS;

  sprintf(formatted_time, "%02d:%02d:%02d:%02d", days, hours, mins, secs);

  return formatted_time;
}

/*
 * outputs the state to stdout.
 * if running in test-mode, then this outputs nothing.
 * The decision to do this is so that testing can be kept clean,
 * and all error-messages can be seen clearly.
 */
void output_state(struct State *state) {
  /* initial state does not have an event attached */

#ifdef DEBUG
  return;
#endif

  if (state->no != 0) {
    printf("%s -> ", format_time(state->time));

    /*
     * This switch statement is an easy way to print out values depending on the state-type.
     * the nature of 'immutable' states guarantees that no information will be lost with multiple types.
     */
    switch (state->event) {
    case PASSENGER_SUBSCRIPTION_EVENT:
      printf("new request placed from stop %d to stop %d for departure at %s scheduled for %s",
             state->passenger_subscription_event->departure,
             state->passenger_subscription_event->arrival,
             format_time(state->passenger_subscription_event->depart_at),
             format_time(state->passenger_subscription_event->scheduled_at));
      break;
    case PASSENGER_EMBARK_EVENT:
      break;
    case PASSENGER_DISEMBARK_EVENT:
      break;
    case BUS_ARRIVAL_EVENT:
      break;
    case BUS_DEPARTURE_EVENT:
      break;
    }

    printf("\n");
  }
}

/*
 * helper function to check whether a vertex is empty or not
 */
#define UNDEFINED -2
int vertex_empty(int *vertex, int length) {
  int i = 0;

  while (i < length) {
    if (vertex[i] == 1) {
      return 1;
    }
    i++;
  }

  return 0;
}

/*
 * returns the index of the minimum vertex.
 */
int min_vertex(int *vertex, int *dist, int length) {
  int i;
  int min = -1;
  int min_vertex = -1;

  for (i = 0; i < length; i++) {
    if (vertex[i] == 1) { /* vertex is in the set */
      if (min == -1 || dist[i] < min) {
        min_vertex = i;
        min = dist[i];
      }
    }
  }

  return min_vertex;
}

/*
 * Checks whether two stops are adjacent
 *
 * Returns -1 on failure
 */
int stop_adjacent(struct State *state, int source, int dest) {
  if (source == dest) return -1;

  int adjacent = state->stops[source].adjacent;
  struct Stop *stop = &state->stops[source];
  int i;

  for (i = 0; i < adjacent; i++) {
    if (stop->edges[i].dest == dest) {
      return i;
    }
  }

  return -1;
}

/*
 * Find the Shortest route from one location to another.
 *
 * (not fully implemented...)
 */
struct Route *shortest_route(struct State *state, int source, int destination) {
  int no_stops = state->config->no_stops;
  int *vertex = malloc(no_stops * sizeof(int));
  int i, j;

  int *dist = malloc(no_stops * sizeof(int));
  int *prev = malloc(no_stops * sizeof(int));
  /* init vertex 'set' */
  for (i = 0; i < no_stops; i++) {
    vertex[i] = -1;
  }

  for (i = 0; i < state->config->no_stops; i++) {
    dist[i] = INT_MAX;
    prev[i] = UNDEFINED;
    vertex[i] = 1;
  }

  dist[source] = 0;

  while (vertex_empty(vertex, no_stops)) {
    // int stop = 0; /* vertex with min dist from list of distances */
    int stop_id = min_vertex(vertex, dist, no_stops);
    int stop = vertex[stop_id];
    vertex[stop_id] = 0;

    for (j = 0; j < no_stops; j++) {
      /* only stops that are adjacent to current stop */
      int edge_id = stop_adjacent(state, stop, j);
      if (j != stop_id && edge_id >= 0) {
        int alt = dist[stop_id] + state->stops[stop_id].edges[edge_id].weight;

        if (alt < dist[stop_id]) {
          dist[j] = alt;
          prev[j] = stop_id;
        }
      }
    }
  }

  return NULL;
}

/*
 * This method iterates through all the buses,
 * and chooses the closest bus to the passenger, and the travel time.
 *
 * (not fully implemented...)
 */
void passenger_find_shortest_route(struct State *state) {
  int i;
  // struct Stop *p_departure = state->passenger_subscription_event->departure;


  /* loop through buses to find the closest bus */
  for (i = 0; i < state->config->no_buses; i++) {
    // struct Bus *bus = state->buses + i;

    /* the location of the bus in my walk */
    // int walk_location = bus->location;
    /* TODO: probably need to setup a costing thing here... */

    /* walk along a possible path while seeing the expense of it */

    /* do some magic here to save the minimum route */
  }
}


/*
 * gets the next passenger subscription state
 */
struct State *next_passenger_state(struct State *old_state) {
  double r;
  double request_rate = old_state->config->request_rate;
  struct State *state = next_state(old_state);
  state->event = PASSENGER_SUBSCRIPTION_EVENT;
  state->passenger_subscription_event = malloc(sizeof(struct PassengerSubscriptionEvent));
  state->passenger_subscription_event->no = 0;


  /* stops must be uniformly random */
  state->passenger_subscription_event->departure = (int) random_value(request_rate, state->config->no_stops);
  state->passenger_subscription_event->arrival = (int) random_value(request_rate, state->config->no_stops);

  /* get wait time for passenger */
  {
    r = random_value(request_rate, 0);
    int next_passenger = r;
    state->time = old_state->time + next_passenger;
  }
  r = random_value(request_rate, 0);
  {
    int depart_time = r;
    state->passenger_subscription_event->depart_at = state->time + depart_time;

    /*
     * set this to the same time as the default
     * this will be set to the calculated estimated arrival time for pickup.
     */
    state->passenger_subscription_event->scheduled_at = state->passenger_subscription_event->depart_at;
  }

  /* choose a bus to pick up the current passenger */
  passenger_find_shortest_route(state);
  return state;
}

/*
 * This returns the state of the next event.
 * it gets the possible states of the next possible states,
 * then iterates through them and finds the one with the shortest time to
 * execution.
 *
 * TODO: Calculate the estimated pickup time for passenger subscriptions
 */
struct State *create_new_state(struct State *old_state) {
  struct State *pickup = next_passenger_state(old_state);
  return pickup;
}
/*
 * This method performs one tick, and returns the new state.
 *
 * The purpose of this method is to not mutate the passed in state,
 * but instead return a new state with a reference to the previous state.
 */
struct State *tick(struct State *state) {
  state = create_new_state(state);
  return state;
}

/*
 * This method sets up some basic things, then gets to work on the problem.
 *
 * this is the working method. it sets up anything relevant to running the experiment,
 * then runs the experiment until the defined finish.
 */
struct Stats *run_experiment(struct State *state) {
  struct Stats *stats = new_stats();
  srand((int)time(NULL));
  rand(); /* calling once because first value is always the same */


  while (state->time < state->config->stop_time) {
    // TODO: add an event printer to the project.
    output_state(state);
    state = tick(state);
  }

  stats->state = state;
  return stats;
}
