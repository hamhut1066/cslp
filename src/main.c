#include <stdio.h>
#include <stdlib.h>

#include "read_file.h"

void usage() {
  printf("Usage: cslp [filename]\n");
}

int main(int argc, char *argv[]) {
  struct Config config;

  if (argc < 2) {
    usage();
    return 0;
  }

  /* Initialise and allocate base objects. */
  read_config_file(&config, argv[1]);
  print_config(&config);

  /* Cleanup of assigned variables */
  /* wg_delete_local_database(db); */
  destroy_config(&config);
  return 0;
}
