#include "matrix_sparse_private.h"

void matrix_sparse_vector_multiply_add(
	double * y,
  const matrix_sparse * a,
  const double * x)
{
  cs a0;
  
  matrix_sparse_to_cs(&a0, a);
  cs_gaxpy(&a0, x, y);
}
