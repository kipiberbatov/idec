#include "mesh.h"

/* it is assumed that (p != q) */
void mesh_fcn_part2(jagged1 * m_fcn_q_p, const mesh * m, int q, int p)
{
  jagged3 m_fcn;

  m_fcn.a0 = m->fc->a0;
  m_fcn.a1 = m->fc->a1;
  m_fcn.a2 = m->fc->a2;
  m_fcn.a3 = m->fc->a3;
  jagged3_part2(m_fcn_q_p, &m_fcn, q, p - q - 1);
}
