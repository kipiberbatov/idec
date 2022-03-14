#include <errno.h>
#include <stdlib.h>
#include "imath.h"
#include "mesh_brick.h"

int * mesh_brick_cf_a3(int m_cf_a3_size, int m_dim, const int * m_cn)
{
  int i, ind, m_cn_p, m_cfn_p_q, p, q, r;
  int * m_cf_a3;
  
  m_cf_a3 = (int *) malloc(m_cf_a3_size * sizeof(int));
  if (errno)
  {
    perror("Cannot allocate memory for m_cf_a3");
    return NULL;
  }
  ind = 0;
  for (p = 1; p <= m_dim; ++p)
  {
    m_cn_p = m_cn[p];
    for (q = 0; q < p; ++q)
    {
      r = p - q;
      m_cfn_p_q = (1 << r) * imath_binom(p, r);
      for (i = 0; i < m_cn_p; ++i)
      {
        m_cf_a3[ind] = m_cfn_p_q;
        ++ind;
      }
    }
  }
  return m_cf_a3;
}
