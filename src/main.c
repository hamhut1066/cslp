#include <stdio.h>
#include <stdlib.h>

#include "read_file.h"
#include "controller.h"

void usage() {
  printf("Usage: cslp [filename]\n");
}

int main(int argc, char *argv[]) {
  State *state;
  struct Config config;

  if (argc < 2) {
    usage();
    return 0;
  }

  /* Initialise and allocate base objects. */
  read_config_file(&config, argv[1]);
  state = get_state(&config);


  run_experiment(state);
  /* Cleanup of assigned variables */
  /* wg_delete_local_database(db); */
  destroy_config(&config);
  return 0;
}
