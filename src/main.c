#include <stdio.h>
#include <stdlib.h>
#include "whitedb/whitedb.h"

#include "debug.h"

#include "read_file.h"

void usage() {
  printf("Usage: cslp [filename]\n");
}

int main(int argc, char *argv[]) {
  config_t config;
  void *db;
  void *rec, *rec2;
  wg_int enc, enc2;

  if (argc < 2) {
    usage();
    return 0;
  }

  DEBUG_PRINT("Hello World\n");

  /* Initialise and allocate base objects. */
  read_config_file(&config, argv[1]);
  db = wg_attach_database("1000", 2000000);

  rec = wg_create_record(db, 10);
  rec2 = wg_create_record(db, 2);

  enc = wg_encode_int(db, 443);
  enc2 = wg_encode_str(db, "this is my string!", NULL);

  wg_set_field(db, rec, 7, enc);
  wg_set_field(db, rec2, 0, enc2);

  /* Cleanup of assigned variables */
  config_destroy(&config);
  /* wg_delete_local_database(db); */
  return 0;
}
