#include "double_array_private.h"
#include "double_matrix_private.h"

void double_matrix_file_print_raw(FILE * out, int m, int n, const double * a)
{
  int i, ind;

  ind = 0;
  for (i = 0; i < m; ++i)
  {
    double_array_file_print_raw(out, n, a + ind);
    ind += n;
  }
}
