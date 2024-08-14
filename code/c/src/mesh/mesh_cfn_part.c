#include "mesh.h"

/* it is assumed that (p > q) */
void mesh_cfn_part2(jagged1 * m_cfn_p_q, const mesh * m, int p, int q)
{
  jagged3 m_cfn;

  m_cfn.a0 = m->cf->a0;
  m_cfn.a1 = m->cf->a1;
  m_cfn.a2 = m->cf->a2;
  m_cfn.a3 = m->cf->a3;
  jagged3_part2(m_cfn_p_q, &m_cfn, p - 1, q);
}
