#include "de_rham.h"

void de_rham_0(double * x, const mesh * m, double (*f)(const double *))
{
  int i, m_cn_0, m_dim_embedded;
  double * m_coord;
  
  m_cn_0 = m->cn[0];
  m_dim_embedded = m->dim_embedded;
  m_coord = m->coord;
  
  for (i = 0; i < m_cn_0; ++i)
    x[i] = f(m_coord + m_dim_embedded * i);
}
