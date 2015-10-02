#include <stdio.h>

#include "read_file.h"

void usage() {
  printf("Usage: cslp [filename]\n");
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    usage();
    return 0;
  }

  return 0;
  // return read_config_file(argv);
}
