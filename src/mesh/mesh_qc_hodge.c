#include <errno.h>
#include <stdlib.h>
#include "mesh_qc_private.h"

matrix_sparse * mesh_qc_hodge_p(
  const mesh_qc * m, matrix_sparse ** m_bd, int p,
  const double * m_inner_q, const double * m_coeff_q)
{
  int m_hodge_p_nonzero_max, q;
  matrix_sparse * m_hodge_p;
  
  q = m->dim - p;
  
  m_hodge_p = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (errno)
  {
    fputs("mesh_qc_hodge_p - cannot allocate memory for m_hodge_p\n", stderr);
    goto end;
  }
  
  m_hodge_p->rows = m->cn[q];
  m_hodge_p->cols = m->cn[p];
  
  m_hodge_p->cols_total = (int *) malloc(sizeof(int) * (m->cn[p] + 1));
  if (errno)
  {
    fputs("mesh_qc_hodge_p - cannot allocate memory for "
          "m_hodge_p->cols_total\n", stderr);
    goto m_hodge_p_free;
  }
  mesh_qc_hodge_p_cols_total(m_hodge_p->cols_total, m, p);
  
  m_hodge_p_nonzero_max = m_hodge_p->cols_total[m_hodge_p->cols];
  
  m_hodge_p->row_indices = (int *) malloc(sizeof(int) * m_hodge_p_nonzero_max);
  if (errno)
  {
    fputs("mesh_qc_hodge_p - cannot allocate memory for "
          "m_hodge_p->row_indices\n", stderr);
    goto m_hodge_p_cols_total_free;
  }
  mesh_qc_hodge_p_row_indices(m_hodge_p->row_indices, m, p);
  
  m_hodge_p->values = (double *) malloc(sizeof(double) * m_hodge_p_nonzero_max);
  if (errno)
  {
    fputs("mesh_qc_hodge_p - cannot allocate memory for "
          "m_hodge_p->row_indices\n", stderr);
    goto m_hodge_p_row_indices_free;
  }
  mesh_qc_hodge_p_values(m_hodge_p->values, m, m_bd, p, m_inner_q, m_coeff_q);
  
  return m_hodge_p;
  
  /* cleaning if an error occurs */
m_hodge_p_row_indices_free:
  free(m_hodge_p->row_indices);
m_hodge_p_cols_total_free:
  free(m_hodge_p->cols_total);
m_hodge_p_free:
  free(m_hodge_p);
end:
  return NULL;
}

matrix_sparse ** mesh_qc_hodge(const mesh_qc * m, matrix_sparse ** m_bd, 
                               double ** m_inner, double ** m_coeff)
{
  int m_dim, p, q;
  matrix_sparse ** m_hodge;
  
  m_dim = m->dim;
  
  m_hodge = (matrix_sparse **) malloc(sizeof(matrix_sparse *) * (m_dim + 1));
  if (errno)
  {
    fputs("mesh_qc_hodge - cannot allocate memory for m_hodge\n", stderr);
    return NULL;
  }
  
  for (p = 0; p <= m_dim; ++p)
  {
    q = m_dim - p;
    m_hodge[p] = mesh_qc_hodge_p(m, m_bd, p, m_inner[q], m_coeff[q]);
    if (errno)
    {
      fprintf(stderr,
              "mesh_qc_hodge - cannot allocate memory for m_hodge[%d]\n", p);
      matrix_sparse_array_free(m_hodge, p);
      return NULL;
    }
  }
  
  return m_hodge;
}
