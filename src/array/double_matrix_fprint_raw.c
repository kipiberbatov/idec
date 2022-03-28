#include "double_private.h"

void double_matrix_fprint_raw(FILE * out, int m, int n, const double * a)
{
  int i, ind;
  
  ind = 0;
  for (i = 0; i < m; ++i)
  {
    double_array_fprint(out, n, a + ind, "--raw");
    ind += n;
  }
}
