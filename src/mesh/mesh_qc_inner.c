#include <errno.h>
#include <stdlib.h>
#include "double.h"
#include "mesh_qc.h"
#include "vector_sparse.h"

double * mesh_qc_inner_p(const mesh_qc * m, const double * m_vol_d,
                         int p, vector_sparse ** m_metric_p)
{
  int i, m_cn_p;
  double * m_inner_p;
  
  m_cn_p = m->cn[p];
  
  m_inner_p = (double *) malloc(sizeof(double) * m_cn_p);
  if (errno)
  {
    fprintf(stderr, 
            "mesh_qc_inner_p - cannot allocate memory for m_inner[%d]\n", p);
    return NULL;
  }
  
  for (i = 0; i < m_cn_p; ++i)
    m_inner_p[i] = mesh_qc_integrate(m, m_vol_d, m_metric_p[i]);
  
  return m_inner_p;
}

double ** mesh_qc_inner(
  const mesh_qc * m, const double * m_vol_d, vector_sparse *** m_metric)
{
  int m_dim, p;
  double ** m_inner;
  
  m_dim = m->dim;
  
  m_inner = (double **) malloc(sizeof(double *) * (m_dim + 1));
  if (errno)
  {
    fputs("mesh_qc_inner - cannot allocate memory for m_inner\n", stderr);
    return NULL;
  }
  
  for (p = 0; p <= m_dim; ++p)
  {
    m_inner[p] = mesh_qc_inner_p(m, m_vol_d, p, m_metric[p]);
    if (errno)
    {
      fprintf(stderr, "mesh_qc_inner - cannot calculate m_inner[%d]\n", p);
      double_array2_free(m_inner, p);
      return NULL;
    }
  }
  
  return m_inner;
}
