#include <stdlib.h>
#include "mesh.h"

int * mesh_cf_a1(int m_dim)
{
  int i;
  int * m_cf_a1;
  
  m_cf_a1 = (int *) malloc(m_dim * sizeof(int));
  /* NULL pointer check */
  for (i = 0; i < m_dim; ++i)
    m_cf_a1[i] = i + 1;
  return m_cf_a1;
}

int * mesh_cf_a2(int m_cf_a2_size, int m_dim, const int * m_cn)
{
  int ind, m_cn_p, p, q;
  int * m_cf_a2;
  
  m_cf_a2 = (int *) malloc(m_cf_a2_size * sizeof(int));
  /* NULL pointer check */
  ind = 0;
  for (p = 1; p <= m_dim; ++p)
  {
    m_cn_p = m_cn[p];
    for (q = 0; q < p; ++q)
    {
      m_cf_a2[ind] = m_cn_p;
      ++ind;
    }
  }
  return m_cf_a2;
}
