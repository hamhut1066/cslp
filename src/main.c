#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <stdio.h>

static void null_test_success(int state) {
}
int main(void) {
  null_test_success(2);
  return 0;
}
