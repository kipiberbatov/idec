#include "double_array_file_print_curly.h"

/*
Print to a file an array of doubles in the form {a[0],a[1],...,a[n-1]}.
*/
void double_array_file_print_curly(FILE * out, int n, const double * a)
{
  int i;
  
  fputc('{', out);
  for (i = 0; i < n - 1; ++i)
    fprintf(out, "%g,", a[i]);
  if (n)
    fprintf(out, "%g", a[i]);
  fputc('}', out);
}
