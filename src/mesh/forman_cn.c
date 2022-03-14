#include <stdlib.h>
#include "forman.h"

int * forman_cn(const mesh * m)
{
  int i_f, m_dim, p_f, q_f;
  int * m_cn, * m_forman_cn;
  jagged1 m_cfn_p_r; /* r_f = p_f - q_f */
  
  m_dim = m->dim;
  m_cn = m->cn;
  
  m_forman_cn = (int *) calloc((m_dim + 1), sizeof(int));
  /* NULL pointer check */
  
  for (p_f = 0; p_f <= m_dim; ++p_f)
    m_forman_cn[0] += m_cn[p_f];
  
  for (q_f = 1; q_f <= m_dim; ++q_f)
    for (p_f = q_f; p_f <= m_dim; ++p_f)
    {
      mesh_cfn_part2(&m_cfn_p_r, m, p_f, p_f - q_f);
      for (i_f = 0; i_f < m_cn[p_f]; ++i_f)
        m_forman_cn[q_f] += m_cfn_p_r.a1[i_f];
    }
  return m_forman_cn;
}
