#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_coboundary_star_file_print_raw(
  FILE * out, const mesh_qc * m, matrix_sparse ** m_bd, double ** m_inner)
{
  int m_cbd_star_p_nonzero_max, m_dim, p;
  matrix_sparse * m_cbd_star_p;
  
  m_dim = m->dim;
  for (p = 1; p <= m_dim; ++p)
  {
    m_cbd_star_p =
      mesh_qc_coboundary_star_p(m, p, m_bd[p - 1], m_inner[p], m_inner[p - 1]);
    /* NULL pointer check */
    m_cbd_star_p_nonzero_max = m_cbd_star_p->cols_total[m_cbd_star_p->cols];
    double_array_file_print(
      out, m_cbd_star_p_nonzero_max, m_cbd_star_p->values, "--raw");
    matrix_sparse_free_shared(m_cbd_star_p);
  }
}

int main()
{
  mesh_qc * m;
  matrix_sparse ** m_bd;
  double ** m_inner;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  m = mesh_file_scan(in, "--raw");
  /* NULL pointer check */
  m_bd = mesh_file_scan_boundary(in, m);
  /* NULL pointer check */
  m_inner = double_array2_file_scan(in, m->dim + 1, m->cn, "--raw");
  /* NULL pointer check */
  mesh_qc_coboundary_star_file_print_raw(out, m, m_bd, m_inner);
  /* NULL pointer check */
  double_array2_free(m_inner, m->dim + 1);
  matrix_sparse_array_free(m_bd, m->dim);
  mesh_free(m);
  return 0;
}
