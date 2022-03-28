#include "forman_private.h"
#include "int.h"

void forman_cf_a3(int * m_forman_cf_a3, int m_dim, const int * m_forman_cn)
{
  int ind, m_forman_cn_p_f, p_f, q_f, r_f, vertices_number;

  ind = 0;
  for (p_f = 1; p_f <= m_dim; ++p_f)
  {
    m_forman_cn_p_f = m_forman_cn[p_f];
    for (q_f = 0; q_f < p_f; ++q_f)
    {
      r_f = p_f - q_f;
      vertices_number = (1 << r_f) * int_binomial(p_f, r_f);
      int_array_assign_constant(m_forman_cf_a3 + ind, m_forman_cn_p_f,
                                vertices_number);
      ind += m_forman_cn_p_f;
    }
  }
}
