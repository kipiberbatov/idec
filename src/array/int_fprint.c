#include "int.h"

void int_fprint_array(FILE * out, int n, const int * a)
{
  int i;
  
  fputc('{', out);
  for (i = 0; i < n - 1; ++i)
    fprintf(out, "%d,", a[i]);
  if (n)
    fprintf(out, "%d", a[i]);
  fputc('}', out);
}

void int_fprint_array_annotated(
  FILE * out, int n, const int * a, const char * name)
{
  fputs(name, out);
  fputs(" = ", out);
  int_fprint_array(out, n, a);
  fputs("\n", out);
}

void int_fprint_array_raw(FILE * out, int n, const int * a)
{
  int i;
  
  for (i = 0; i < n - 1; ++i)
    fprintf(out, "%d ", a[i]);
  if (n)
    fprintf(out, "%d\n", a[i]);
}
