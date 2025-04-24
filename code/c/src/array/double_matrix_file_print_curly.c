#include "double_array_private.h"
#include "double_matrix_private.h"

void double_matrix_file_print_curly(FILE * out, int m, int n, const double * a)
{
  int i, ind;

  fputc('{', out);
  ind = 0;
  for (i = 0; i < m - 1; ++i)
  {
    double_array_file_print_curly(out, n, a + ind);
    fputc(',', out);
    ind += n;
  }
  if (m > 0)
    double_array_file_print_curly(out, n, a + ind);
  fputc('}', out);
}
