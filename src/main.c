#include <stdio.h>
#include <stdlib.h>

#include "read_file.h"

void usage() {
  printf("Usage: cslp [filename]\n");
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    usage();
    return 0;
  }
  char **buffer = malloc(BUFF_LEN * sizeof(char*));
  read_config_file(buffer, argv[1]);
  for (int i = 0; i < BUFF_LEN; i++) {
    printf("%s\n", buffer[i]);
  }

  return 0;
}
