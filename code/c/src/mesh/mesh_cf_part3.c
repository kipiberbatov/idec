#include "int.h"
#include "mesh.h"

void mesh_cf_part3(jagged1 * m_cf_p_q_i, const mesh * m, int p, int q, int i)
{
  if (p == q)
  {
    m_cf_p_q_i->a0 = 1;
    m_cf_p_q_i->a1 = m->c + int_array_total_sum(p, m->cn) + i;
  }
  else
    jagged4_part3(m_cf_p_q_i, m->cf, p - 1, q, i);
}
