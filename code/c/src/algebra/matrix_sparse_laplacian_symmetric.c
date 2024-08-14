#include <math.h>
#include "matrix_sparse.h"

static void matrix_sparse_laplacian_symmetric_p(
  matrix_sparse * delta_p, const double * m_inner_p)
{
  int delta_p_cols, i, i_loc, j;
  int * delta_p_cols_total, * delta_p_row_indices;
  double * delta_p_values;

  delta_p_cols = delta_p->cols;
  delta_p_cols_total = delta_p->cols_total;
  delta_p_row_indices = delta_p->row_indices;
  delta_p_values = delta_p->values;

  for (j = 0; j < delta_p_cols; ++j)
  {
    for (i_loc = delta_p_cols_total[j]; i_loc < delta_p_cols_total[j + 1];
         ++i_loc)
    {
      i = delta_p_row_indices[i_loc];
      delta_p_values[i_loc] *= sqrt(m_inner_p[i] / m_inner_p[j]);
    }
  }
}

void matrix_sparse_laplacian_symmetric(
  matrix_sparse ** delta, int d, double ** m_inner)
{
  int p;

  for (p = 0; p <= d; ++p)
    matrix_sparse_laplacian_symmetric_p(delta[p], m_inner[p]);
}
