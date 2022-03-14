#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_cbd_star_fprint(
  FILE * out, const mesh_qc * m, cs ** m_bd, double ** m_inner)
{
  int m_dim, p;
  int * m_cn;
  cs * m_cbd_star_p;
  
  m_dim = m->dim;
  m_cn = m->cn;
  for (p = 1; p <= m_dim; ++p)
  {
    m_cbd_star_p =
      mesh_qc_cbd_star_p(m, p, m_bd[p - 1], m_inner[p], m_inner[p - 1]);
    /* NULL pointer check */
    double_fprint_array_raw(out, m_cbd_star_p->nzmax, m_cbd_star_p->x);
    cs_free_shared(m_cbd_star_p);
  }
}

int main()
{
  mesh_qc * m;
  cs ** m_bd;
  double ** m_inner;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  m = mesh_fscan(in);
  /* NULL pointer check */
  m_bd = mesh_fscan_bd(in, m);
  /* NULL pointer check */
  m_inner = double_fscan_array2(in, m->dim + 1, m->cn);
  /* NULL pointer check */
  mesh_qc_cbd_star_fprint(out, m, m_bd, m_inner);
  /* NULL pointer check */
  double_free_array2(m_inner, m->dim + 1);
  cs_free_array(m_bd, m->dim);
  mesh_free(m);
  return 0;
}
