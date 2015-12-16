#include <stdio.h>
#include <stdlib.h>

#include "read_file.h"
#include "controller.h"
#include "output.h"

void usage() {
  printf("Usage: cslp [filename]\n");
}

int main(int argc, char *argv[]) {
  struct State *state;
  // struct Stats *stats;
  struct Config config;

  if (argc < 2) {
    usage();
    return 0;
  }

  /* Initialise and allocate base objects. */
  read_config_file(&config, argv[1]);
  state = get_state(&config);


  // stats = run_experiment(state);
  run_experiment(state);

  /* Cleanup of assigned variables */
  /* wg_delete_local_database(db); */
  destroy_config(&config);
  return 0;
}
/* hamish was here */
