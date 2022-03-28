#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_cbd_star_fprint_raw(
  FILE * out, const mesh_qc * m, matrix_sparse ** m_bd, double ** m_inner)
{
  int m_cbd_star_p_nonzero_max, m_dim, p;
  int * m_cn;
  matrix_sparse * m_cbd_star_p;
  
  m_dim = m->dim;
  m_cn = m->cn;
  for (p = 1; p <= m_dim; ++p)
  {
    m_cbd_star_p =
      mesh_qc_cbd_star_p(m, p, m_bd[p - 1], m_inner[p], m_inner[p - 1]);
    /* NULL pointer check */
    m_cbd_star_p_nonzero_max = m_cbd_star_p->cols_total[m_cbd_star_p->cols];
    double_array_fprint(
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
  m = mesh_fscan(in, "--raw");
  /* NULL pointer check */
  m_bd = mesh_fscan_bd(in, m);
  /* NULL pointer check */
  m_inner = double_array2_fscan(in, m->dim + 1, m->cn, "--raw");
  /* NULL pointer check */
  mesh_qc_cbd_star_fprint_raw(out, m, m_bd, m_inner);
  /* NULL pointer check */
  double_array2_free(m_inner, m->dim + 1);
  matrix_sparse_array_free(m_bd, m->dim);
  mesh_free(m);
  return 0;
}
