#include <errno.h>

#include "matrix_sparse.h"

matrix_sparse * matrix_sparse_material_product(
  const matrix_sparse * m_cbd_0,
  const double * kappa_1,
  const matrix_sparse * m_cbd_star_1)
{
  matrix_sparse * result, * m_cbd_star_1_material;

  m_cbd_star_1_material = matrix_sparse_copy(m_cbd_star_1);
  if (errno)
  {
    fprintf(stderr,
      "  %s:%d: cannot initialize m_cbd_star_1_material\n",
      __FILE__, __LINE__);
    return NULL;
  }
  matrix_sparse_multiply_with_diagonal_matrix(m_cbd_star_1_material, kappa_1);

  result = matrix_sparse_product(m_cbd_star_1_material, m_cbd_0);
  if (errno)
  {
    fprintf(stderr,
      "  %s:%d: cannot calculate matrix result\n",
      __FILE__, __LINE__);
    matrix_sparse_free(m_cbd_star_1_material);
    return NULL;
  }
  matrix_sparse_free(m_cbd_star_1_material);

  return result;
}
