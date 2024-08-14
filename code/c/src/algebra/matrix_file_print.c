#include "matrix.h"

void matrix_file_print(FILE * out, int d, int n, const double * a)
{
  int p, i;
  for (p = 0; p < d; ++p)
  {
    for (i = 0; i < n - 1; ++i)
      fprintf(out, "%g ", a[i * d + p]);
    fprintf(out, "%g\n", a[i * d + p]);
  }
}
