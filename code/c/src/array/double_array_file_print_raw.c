#include "double_array_private.h"

void double_array_file_print_raw(FILE * out, int n, const double * a)
{
  int i;

  for (i = 0; i < n - 1; ++i)
    fprintf(out, "%g ", a[i]);
  if (n)
    fprintf(out, "%g\n", a[i]);
}
