#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_metric_fprint(
  FILE * out, const mesh_qc * m, double ** m_vol)
{
  int i, m_dim, p;
  int * m_cn;
  vec_sparse ** m_metric_p;
  
  m_dim = m->dim;
  m_cn = m->cn;
  /* NULL pointer check */
  for (p = 0; p <= m_dim; ++p)
  {
    m_metric_p = mesh_qc_metric_p(m, p, m_vol[p]);
    /* NULL pointer check */
    for (i = 0; i < m_cn[p]; ++i)
      double_fprint_array_raw(out, m_metric_p[i]->nzmax, m_metric_p[i]->x);
    vec_sparse_free_array(m_metric_p, m_cn[p]);
  }
}

int main()
{
  int m_dim;
  mesh_qc * m;
  cs ** m_bd;
  double ** m_vol;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  m = mesh_fscan(in);
  /* NULL pointer check */
  m_dim = m->dim;
  m_bd = mesh_fscan_bd(in, m);
  /* NULL pointer check */
  m_vol = double_fscan_array2(in, m_dim + 1, m->cn);
  /* NULL pointer check */
  mesh_qc_metric_fprint(out, m, m_vol);
  /* NULL pointer check */
  double_free_array2(m_vol, m_dim + 1);
  cs_free_array(m_bd, m_dim);
  mesh_free(m);
  return 0;
}
