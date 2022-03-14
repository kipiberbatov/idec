#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_hodge_fprint(FILE * out, const mesh_qc * m, cs ** m_bd,
                                 double ** m_inner, double ** m_coeff)
{
  int m_dim, p, q;
  cs * m_hodge_p;
  
  m_dim = m->dim;
  for (p = 0; p <= m_dim; ++p)
  {
    q = m_dim - p;
    m_hodge_p = mesh_qc_hodge_p(m, m_bd, p, m_inner[q], m_coeff[q]);
    /* NULL pointer check */
    cs_fprint(out, m_hodge_p, "--raw");
    free(m_hodge_p);
  }
}

int main()
{
  int m_dim;
  int * m_cn;
  mesh_qc * m;
  cs ** m_bd;
  double ** m_inner, ** m_coeff;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  m = mesh_fscan(in);
  /* NULL pointer check */
  m->fc = mesh_fc(m);
  /* NULL pointer check */
  m_dim = m->dim;
  m_cn = m->cn;
  m_bd = mesh_fscan_bd(in, m);
  /* NULL pointer check */
  m_inner = double_fscan_array2(in, m_dim + 1, m_cn);
  /* NULL pointer check */
  m_coeff = double_fscan_array2(in, m_dim + 1, m_cn);
  /* NULL pointer check */
  mesh_qc_hodge_fprint(out, m, m_bd, m_inner, m_coeff);
  /* NULL pointer check */
  double_free_array2(m_coeff, m_dim + 1);
  double_free_array2(m_inner, m_dim + 1);
  cs_free_array(m_bd, m_dim);
  mesh_free(m);
  return 0;
}
