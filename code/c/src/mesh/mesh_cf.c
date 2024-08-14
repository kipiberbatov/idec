#include "int.h"
#include "mesh_private.h"

void mesh_cf_a1(int * m_cf_a1, int m_dim)
{
  int i;

  for (i = 0; i < m_dim; ++i)
    m_cf_a1[i] = i + 1;
}

void mesh_cf_a2(int * m_cf_a2, int m_dim, const int * m_cn)
{
  int ind, p;

  ind = 0;
  for (p = 1; p <= m_dim; ++p)
  {
    int_array_assign_constant(m_cf_a2 + ind, p, m_cn[p]);
    ind += p;
  }
}
