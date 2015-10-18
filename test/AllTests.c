#include <stdio.h>
#include <stdlib.h>

#include "cutest/CuTest.h"

#include "read_file_test.h"

void RunAllTests(void) {
  CuString *output = CuStringNew();
  CuSuite* suite = CuSuiteNew();

  /* new tests here */
  CuSuiteAddSuite(suite, ReadFileGetSuite());

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s", output->buffer);

  free(output);
  free(suite);
}

int main(void) {
  RunAllTests();
}
