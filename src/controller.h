#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "states.h"

struct Stats *run_experiment(struct State *state);

/* exports for testing only */
struct State *tick(struct State *state);
#endif
