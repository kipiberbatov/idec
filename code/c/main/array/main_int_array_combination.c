#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "int.h"

static void int_array_combination_file_print(FILE * out, int m, int n)
{
  int prod, i;
  int * a;

  prod = int_binomial(m, n);
  a = (int *) malloc(n * sizeof(int));
  if (errno)
  {
    perror("int_array_combination_file_print - cannot allocate memory for a");
    return;
  }
  int_array_assign_identity(a, n);
  i = 0;
  while(i < prod - 1)
  {
    int_array_file_print(out, n, a, "--raw");
    int_array_combination_next(a, m, n);
    ++i;
  }
  int_array_file_print(out, n, a, "--raw");
  free(a);
}

int main(int argc, char * argv[])
{
  int m, n;

  m = atoi(argv[1]);
  n = atoi(argv[2]);
  int_array_combination_file_print(stdout, m, n);
  if (errno)
  {
    perror("main - printing error");
    goto end;
  }
end:
  return errno;
}
