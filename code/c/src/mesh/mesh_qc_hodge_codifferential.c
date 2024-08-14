#include <errno.h>
#include <stdlib.h>
#include "mesh.h"

matrix_sparse * mesh_qc_hodge_codifferential_p(
  int m_dim, int p, const matrix_sparse * m_cbd_m_dim_minus_p,
  matrix_sparse ** m_hodge)
{
  matrix_sparse * tmp, * m_hodge_codifferential_p;

  tmp = matrix_sparse_product(m_cbd_m_dim_minus_p, m_hodge[p]);
  if (errno)
  {
    perror("During the calculation of d*");
    matrix_sparse_free(tmp);
    return NULL;
  }
  //matrix_sparse_file_print_matrix_form_curly(stderr, tmp);
  m_hodge_codifferential_p = matrix_sparse_product(m_hodge[m_dim - p + 1], tmp);
  if (errno)
  {
    perror("During the calculation of *d*");
    matrix_sparse_free(m_hodge_codifferential_p);
    matrix_sparse_free(tmp);
    return NULL;
  }
  matrix_sparse_free(tmp);
  return m_hodge_codifferential_p;
}

matrix_sparse ** mesh_qc_hodge_codifferential(
  int m_dim, const matrix_sparse * const * m_cbd, matrix_sparse ** m_hodge)
{
  int p;
  matrix_sparse ** m_hodge_codifferential;

  m_hodge_codifferential =
    (matrix_sparse **) malloc(sizeof(matrix_sparse *) * m_dim);
  if (errno)
  {
    perror("During memory allocation for m_hodge_codifferential");
    return NULL;
  }
  for (p = 1; p <= m_dim; ++p)
  {
    m_hodge_codifferential[p - 1] =
      mesh_qc_hodge_codifferential_p(m_dim, p, m_cbd[m_dim - p], m_hodge);
    if (errno)
    {
      fprintf(stderr, "During the calculation of *d*_%d", p);
      perror("");
      matrix_sparse_array_free(m_hodge_codifferential, m_dim);
      return NULL;
    }
  }
  return m_hodge_codifferential;
}
