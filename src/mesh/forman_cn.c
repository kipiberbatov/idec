#include <errno.h>
#include <stdlib.h>
#include "forman_private.h"
#include "int.h"

void forman_cn(int * m_forman_cn, const mesh * m)
{
  int m_dim, p_f, q_f;
  int * m_cn;
  jagged1 m_cfn_p_f_r_f; /* r_f = p_f - q_f */
  
  m_dim = m->dim;
  m_cn = m->cn;
  
  /* q_f = 0 */
  m_forman_cn[0] = int_array_total_sum(m_dim + 1, m_cn);
  
  /* q_f > 0 */
  for (q_f = 1; q_f <= m_dim; ++q_f)
  {
    for (p_f = q_f; p_f <= m_dim; ++p_f)
    {
      mesh_cfn_part2(&m_cfn_p_f_r_f, m, p_f, p_f - q_f);
      m_forman_cn[q_f] += int_array_total_sum(m_cn[p_f], m_cfn_p_f_r_f.a1);
    }
  }
}
