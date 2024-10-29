#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "int.h"

static void int_array_cartesian_product_file_print(FILE * out, int d, const int * n)
{
  int prod, i;
  int * a;

  prod = int_array_total_product(d, n);
  a = (int *) calloc(d, sizeof(int));
  if (errno)
  {
    perror("int_array_cartesian_product_file_print - cannot allocate memory for a");
    return;
  }
  i = 0;
  while(i < prod - 1)
  {
    int_array_file_print(out, d, a, "--raw");
    int_array_cartesian_product_next(a, d, n);
    ++i;
  }
  int_array_file_print(out, d, a, "--raw");
  free(a);
}

int main(int argc, char ** argv)
{
  int d, p;
  int * n;

  d = argc - 1;
  n = (int *) malloc(sizeof(int) * d);
  if (errno)
  {
    perror("main - Cannot allocate memory for n");
    goto end;
  }
  for (p = 0; p < d; ++p)
    n[p] = atoi(argv[1 + p]);
  int_array_cartesian_product_file_print(stdout, d, n);
  if (errno)
  {
    perror("main - printing error");
    goto n_free;
  }
n_free:
  free(n);
end:
  return errno;
}
