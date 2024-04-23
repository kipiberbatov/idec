#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "double.h"
#include "mesh.h"

static void mesh_boundary_p_cols_total(
  int * m_bd_p_cols_total, int m_bd_p_cols, const int * m_cfn_p_q_a1)
{
  int i;
  
  m_bd_p_cols_total[0] = 0;
  for (i = 0; i < m_bd_p_cols; ++i)
    m_bd_p_cols_total[i + 1] = m_bd_p_cols_total[i] + m_cfn_p_q_a1[i];
}

matrix_sparse * mesh_file_scan_boundary_p(FILE * in, const mesh * m, int p)
{
  int m_bd_p_nonzero_max;
  jagged1 m_cfn_p_q; /* q = p - 1 */
  jagged2 m_cf_p_q; /* q = p - 1 */
  matrix_sparse * m_bd_p;
  
  mesh_cfn_part2(&m_cfn_p_q, m, p, p - 1);
  mesh_cf_part2(&m_cf_p_q, m, p, p - 1);

  m_bd_p = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (errno)
  {
    fprintf(stderr,
            "mesh_file_scan_boundary_p - cannot allocate memory for m->bd[%d]\n", p);
    goto end;
  }
  
  m_bd_p->rows = m->cn[p - 1];
  m_bd_p->cols = m->cn[p];
  
  m_bd_p->cols_total = (int *) malloc(sizeof(int) * (m_bd_p->cols + 1));
  if (errno)
  {
    fprintf(stderr, "mesh_file_scan_boundary_p - cannot allocate memory for "
            "m->bd[%d]->cols_total\n", p);
    goto m_bd_p_free;
  }
  mesh_boundary_p_cols_total(m_bd_p->cols_total, m_bd_p->cols, m_cfn_p_q.a1);
  
  m_bd_p_nonzero_max = m_bd_p->cols_total[m_bd_p->cols];
  
  m_bd_p->row_indices = (int *) malloc(sizeof(int) * m_bd_p_nonzero_max);
  if (errno)
  {
    fprintf(stderr, "mesh_file_scan_boundary_p - cannot allocate memory for "
            "m->bd[%d]->row_indices\n", p);
    goto m_bd_p_cols_total_free;
  }
  memcpy(m_bd_p->row_indices, m_cf_p_q.a2, sizeof(int) * m_bd_p_nonzero_max);
  
  m_bd_p->values = double_array_file_scan(in, m_bd_p_nonzero_max, "--raw");
  if (errno)
  {
    fprintf(stderr, "mesh_file_scan_boundary_p - cannot scan m->bd[%d]->values\n", p);
    goto m_bd_p_row_indices_free;
  }
  
  return m_bd_p;
  
  /* cleaning if an error occurs */
m_bd_p_row_indices_free:
  free(m_bd_p->row_indices);
m_bd_p_cols_total_free:
  free(m_bd_p->cols_total);
m_bd_p_free:
  free(m_bd_p);
end:
  return NULL;
}

matrix_sparse ** mesh_file_scan_boundary(FILE * in, const mesh * m)
{
  int m_dim, p;
  matrix_sparse ** m_bd;
  
  m_dim = m->dim;
  
  m_bd = (matrix_sparse **) malloc(sizeof(matrix_sparse *) * m_dim);
  if (errno)
  {
    fputs("mesh_file_scan_boundary - cannot allocate memory for m->bd\n", stderr);
    return NULL;
  }
  
  for (p = 1; p <= m_dim; ++p)
  {
    m_bd[p - 1] = mesh_file_scan_boundary_p(in, m, p);
    if (errno)
    {
      fprintf(stderr, "mesh_file_scan_boundary - cannot scan m->bd[%d]\n", p - 1);
      matrix_sparse_array_free(m_bd, p - 1);
      return NULL;
    }
  }
  
  return m_bd;
}
