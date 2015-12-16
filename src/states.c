#include <stdlib.h>

#include "states.h"
#include "debug.h"
/*
 * Handles all state related things
 */

struct State *get_initial_state() {
  struct State *state = malloc(sizeof(struct State));
  if (state == NULL) {
    printf("Error Mallocing State\n");
    free(state);
    return NULL;
  }

  state->users = NULL;
  state->stops = NULL;
  state->buses = NULL;

  state->no = 0; /* TODO: ? maybe let user define the no? */
  state->time = 0; /* initial state is time 0 */

  return state;
}

struct Config *get_initial_config() {
  struct Config *config = malloc(sizeof(struct Config));
  if (config == NULL) {
    printf("Error mallocing Config\n");
    free(config);
    return NULL;
  }

  /* this default is needed to stop errors */
  config->no_stops = 0;

  return config;
}


void destroy_users(struct User *users) {
  if (users != NULL) {
    printf("%p", users);
    DEBUG_PRINT(">This needs to go through the array and delete everything");
    exit(EXIT_FAILURE);
    free(users);
  }
}

void destroy_buses(struct Bus *buses) {
  if (buses != NULL) {
    // TODO: figure out how to actually run this for the _actual_ length of the array.
    free(buses);
  }
}

void destroy_network(int **map, int dim) {
  int i;
  for(i = 0; i < dim; i++) {
    free(map[i]);
  }
  free(map);
}
void destroy_config(struct Config *conf) {
  if (conf != NULL) {
    destroy_network(conf->map, conf->no_stops);
  }
}

void destroy_state(struct State *state) {
  if (state != NULL) {
    destroy_users(state->users);
    destroy_buses(state->buses);
  }
}

void destroy_stats(struct Stats *stats) {
  if (stats != NULL) {
    destroy_state(stats->state);
  }
}

void print_config(struct Config *config) {
  printf("{busCapacity: %d, boardingTime: %d, requestRate: %f, pickupInterval: %f, maxDelay: %d, noBuses: %d, noStops: %d, stopTime: %d}\n",
         config->bus_capacity,
         config->boarding_time,
         config->request_rate,
         config->pickup_interval,
         config->max_delay,
         config->no_buses,
         config->no_stops, // dimension of map
         config->stop_time
         );
  int i, j;
  if (config->map != NULL) {
    for(i = 0; i < config->no_stops; i++) {
      printf("[");
      for(j = 0; j < config->no_stops; j++) {
        if (config->map[i] != NULL) {
          printf("%dn ", config->map[i][j]);
        } else {
          printf("N ");
        }
      }
      printf("]\n");
    }
  }
}

struct Stats *new_stats() {
  struct Stats *stats = malloc(sizeof(struct Stats));

  return stats;
}


void print_bus(struct Bus *bus) {
  printf("Bus: %d at ", bus->no);
  printf("(%d -> %d)\n", bus->location->no, bus->destination->no);
}

void print_stop(struct Stop *stop) {
  printf("%p\n", stop);
  printf("Stop: %d - (%d)[", stop->no, stop->adjacent);

  int i;
  for (i = 0; i < stop->adjacent; i++) {
    printf("(%d -> %d)", (stop->edges +i)->weight, (stop->edges + i)->dest);
  }

  printf("]\n");
}
void print_state(struct State *state) {
  printf("No: %d - ", state->no);
  printf("Time: %d\n", state->time);

  int i;
  for(i = 0; i < state->config->no_buses; i++) {
    print_bus(state->buses + i);
  }

  for (i = 0; i < state->config->no_stops; i++) {
    print_stop(state->stops + i);
  }
}

/*
 * gets the initial state, and populates it with the config.
 * creates the bus stops too, so that all can be right and pure
 */
struct State *get_state(struct Config *config) {
  int i;
  int j;
  struct State *state;

  state = get_initial_state();
  /* a reference to the config struct is kept accessible in each state for simplicity. */
  state->config = config;

  /* construct the stops */
  state->stops = malloc(config->no_stops * sizeof(struct Stop));

  for (i = 0; i < config->no_stops; i++) {
    struct Stop *stop = malloc(sizeof(struct Stop));
    stop->no = i;
    stop->adjacent = 0;
    /* TODO: think of a more memory-efficient away to do this.
     *
     * This is blatatantly wasting memory, but it guarantees that there won't be a buffer overflow.
     */
    stop->edges = malloc(config->no_stops * sizeof(struct StopEdge));
    state->stops[i] = *stop;
  }

  /* construct the nodes */
  i = 0; j = 0;
  for (i = 0; i < config->no_stops; i++) {
    for (j = 0; j < config->no_stops; j++) {
      int weight = config->map[i][j];
      if (weight != -1 && weight != 0) {
        struct StopEdge *edge = malloc(sizeof(struct StopEdge));
        int index = state->stops[i].adjacent;



        /* assign things */
        edge->weight = weight;

        /* why aren't these working?!!!! */
        // ((state->stops + i)->edges + j)->source = (state->stops + i);
        // ((state->stops + i)->edges + j)->dest = (state->stops + j);

        edge->source = i;
        edge->dest = j;

        (state->stops + i)->adjacent++;

        /* assign new struct into state */
        (state->stops + i)->edges[index] = *edge;
      }
    }
  }

  /* construct the buses */
  state->buses = malloc(config->no_buses * sizeof(struct Bus));
  for (i = 0; i < config->no_buses; i++) {
    (state->buses + i)->no = i;

    /* set the stops to the initial stop */
    (state->buses + i)->location = state->stops;
    (state->buses + i)->destination = state->stops;
  }

  return state;
}

struct State *next_state(struct State *old_state) {

  struct State *state = get_initial_state();
  state->last = old_state;

  state->no = old_state->no + 1;
  state->config = old_state->config;
  state->time = old_state->time;

  state->buses = old_state->buses;
  state->stops = old_state->stops;
  return state;
}



/* IList Methods */

/*
 * Adds an element to the list
 */
void ilist_add(struct IList *list, int value) {
  if (list->length == 0) {
    list->value = value;
    list->length++;
  } else {
    struct IList *next = malloc(sizeof(struct IList));

    next->value = value;


    list->next = next;

    list->length++;
  }
}

/*
 * checks whether the element is contained within the list.
 *
 * returns 1 for true, 0 otherwise
 */
int ilist_contains(struct IList *list, int value) {
  struct IList *element = list;
  int i;

  for (i = 0; i < list->length; i++) {
    if (element->value == value) {
      return 1;
    }

    element = element->next;
  }

  return 0;
}

void free_ilist(struct IList *list) {
  struct IList *iterator = list;
  int i;

  for (i = 0; i < list->length - 1; i++) {
    free(iterator);
    iterator = list->next;
  }
}
