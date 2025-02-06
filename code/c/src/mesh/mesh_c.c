#include "mesh_private.h"

void mesh_c(int * m_c, int m_dim, const int * m_cn)
{
  int i, ind, p;

  ind = 0;
  for (p = 0; p <= m_dim; ++p)
    for (i = 0; i < m_cn[p]; ++i)
    {
      m_c[ind] = i;
      ++ind;
    }
}
