#include "double.h"
#include "mesh_qc.h"
#include "vec_sparse.h"

static void mesh_qc_inner_fprint(
  FILE * out, const mesh_qc * m,
  const double * m_vol_m_dim, vec_sparse *** m_metric)
{
  int m_dim, p;
  int * m_cn;
  double * m_inner_p;
  
  m_dim = m->dim;
  m_cn = m->cn;
  for (p = 0; p <= m_dim; ++p)
  {
    m_inner_p = mesh_qc_inner_p(m, m_vol_m_dim, p, m_metric[p]);
    /* NULL pointer check */
    double_fprint_array_raw(out, m_cn[p], m_inner_p);
    free(m_inner_p);
  }
}

void mesh_qc_inner_fprint_fscan(FILE * out, FILE * in)
{
  int m_dim;
  int * m_cn;
  mesh_qc * m;
  cs ** m_bd;
  double ** m_vol;
  vec_sparse *** m_metric;
  
  m = mesh_fscan(in);
  /* NULL pointer check */
  m_dim = m->dim;
  m_cn = m->cn;
  m_bd = mesh_fscan_bd(in, m);
  /* NULL pointer check */
  m_vol = double_fscan_array2(in, m_dim + 1, m_cn);
  /* NULL pointer check */
  m_metric = mesh_qc_metric_fscan(in, m);
  /* NULL pointer check */
  mesh_qc_inner_fprint(out, m, m_vol[m_dim], m_metric);
  /* NULL pointer check */
  vec_sparse_free_array2(m_metric, m_dim + 1, m_cn);
  double_free_array2(m_vol, m_dim + 1);
  cs_free_array(m_bd, m_dim);
  mesh_free(m);
}

int main()
{
  int m_dim;
  int * m_cn;
  mesh_qc * m;
  cs ** m_bd;
  double ** m_vol;
  vec_sparse *** m_metric;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  m = mesh_fscan(in);
  /* NULL pointer check */
  m_dim = m->dim;
  m_cn = m->cn;
  m_bd = mesh_fscan_bd(in, m);
  /* NULL pointer check */
  m_vol = double_fscan_array2(in, m_dim + 1, m_cn);
  /* NULL pointer check */
  m_metric = mesh_qc_metric_fscan(in, m);
  /* NULL pointer check */
  mesh_qc_inner_fprint(out, m, m_vol[m_dim], m_metric);
  /* NULL pointer check */
  vec_sparse_free_array2(m_metric, m_dim + 1, m_cn);
  double_free_array2(m_vol, m_dim + 1);
  cs_free_array(m_bd, m_dim);
  mesh_free(m);
  return 0;
}
