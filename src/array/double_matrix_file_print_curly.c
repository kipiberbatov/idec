#include "double_private.h"

void double_matrix_file_print_curly(FILE * out, int m, int n, const double * a)
{
  int i, ind;

  fputc('{', out);
  ind = 0;
  for (i = 0; i < m - 1; ++i)
  {
    double_array_file_print(out, n, a + ind, "--curly");
    fputc(',', out);
    ind += n;
  }
  if (m > 0)
    double_array_file_print(out, n, a + ind, "--curly");
  fputc('}', out);
}
