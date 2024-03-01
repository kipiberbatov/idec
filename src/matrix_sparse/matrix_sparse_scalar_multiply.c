#include "matrix_sparse.h"

void matrix_sparse_scalar_multiply(matrix_sparse * a, double lambda)
{
  int nonzero_max = a->cols_total[a->rows];
  int i;
  double * values = a->values;

  for (i = 0; i < nonzero_max; ++i)
    values[i] *= lambda;
}
