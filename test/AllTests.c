#include "CuTest.h"
#include <stdio.h>

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
}

int main(void) {
  RunAllTests();
}
