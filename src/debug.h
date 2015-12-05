#include <stdio.h>
#ifdef DEBUG
#ifndef _DEBUG_H
#define _DEBUG_H
#define DEBUG_PRINT(x) printf(x); printf("\n")
#define PRINT_OPAQUE_STRUCT(p)  print_mem((p), sizeof(*(p)))
#endif
#else
#define DEBUG_PRINT(x) do {} while (0)
#endif

void print_mem(void const *vp, size_t n)
{
  unsigned char const *p = vp;
  for (size_t i=0; i<n; i++)
    printf("%02x\n", p[i]);
  putchar('\n');
};
