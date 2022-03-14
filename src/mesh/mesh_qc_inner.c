#include "mesh_qc.h"
#include "vec_sparse.h"

double * mesh_qc_inner_p(const mesh_qc * m, const double * m_vol_m_dim,
                         int p, vec_sparse ** m_metric_p)
{
  int i, m_cn_p;
  double * m_inner_p;
  
  m_cn_p = m->cn[p];
  m_inner_p = (double *) malloc(m_cn_p * sizeof(double));
  /* NULL pointer check */
  for (i = 0; i < m_cn_p; ++i)
    m_inner_p[i] = mesh_qc_integrate(m, m_vol_m_dim, m_metric_p[i]);
  return m_inner_p;
}

double ** mesh_qc_inner(
  const mesh_qc * m, const double * m_vol_m_dim, vec_sparse *** m_metric)
{
  int m_dim, p;
  double ** m_inner;
  
  m_dim = m->dim;
  m_inner = (double **) malloc((m_dim + 1) * sizeof(double *));
  /* NULL pointer check */
  for (p = 0; p <= m_dim; ++p)
  {
    m_inner[p] = mesh_qc_inner_p(m, m_vol_m_dim, p, m_metric[p]);
    /* NULL pointer check */
  }
  return m_inner;
}
