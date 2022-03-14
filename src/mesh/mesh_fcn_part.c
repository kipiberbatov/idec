#include "mesh.h"

/* it is assumed that (p != q) */
void mesh_fcn_part2(jagged1 * m_fcn_q_p, const mesh * m, int q, int p)
{
  jagged3 m_fcn;
  jagged4 * m_fc;
  
  m_fc = m->fc;
  jagged3_set(&m_fcn, m->dim, m_fc->a1, m_fc->a2, m_fc->a3);
  jagged3_part2(m_fcn_q_p, &m_fcn, q, p - q - 1);
}

int mesh_fcn_part3(const mesh * m, int q, int p, int j)
{
  if (q == p)
    return 1;
  jagged3 m_fcn;
  jagged3_set(&m_fcn, m->dim, m->fc->a1, m->fc->a2, m->fc->a3);
  return jagged3_part3(&m_fcn, q, p - q - 1, j);
}