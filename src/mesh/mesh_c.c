#include <stdlib.h>
#include "list.h"
#include "mesh.h"

int * mesh_c(int m_dim, const int * m_cn)
{
  int i, ind, m_c_size, p;
  int * m_c;
  
  m_c_size = list_sum(m_cn, 0, m_dim + 1);
  m_c = (int *) malloc(m_c_size * sizeof(int));
  /* NULL pointer check */
  ind = 0;
  for (p = 0; p <= m_dim; ++p)
    for (i = 0; i < m_cn[p]; ++i)
    {
      m_c[ind] = i;
      ++ind;
    }
  return m_c;
}