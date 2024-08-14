#include "int_private.h"

void int_array_file_print_curly(FILE * out, int n, const int * a)
{
  int i;

  fputc('{', out);
  for (i = 0; i < n - 1; ++i)
    fprintf(out, "%d,", a[i]);
  if (n)
    fprintf(out, "%d", a[i]);
  fputc('}', out);
}
