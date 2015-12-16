#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "states.h"

struct Stats *run_experiment(struct State *state);

/* exports for testing only */
struct State *tick(struct State *state);
char *format_time(int time);
struct Route *shortest_route(struct State *state, int source, int destination);
int min_vertex(int *vertex, int *dist, int length);
int stop_adjacent(struct State *state, int source, int dest);
#endif
