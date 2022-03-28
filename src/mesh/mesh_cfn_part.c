#include "mesh.h"

// void mesh_cfn_part2(jagged1 * m_cfn_p_q, const mesh * m, int p, int q)
// {
//   jagged3 m_cfn;
//
//   if (p == q)
//   {
//     m_cfn_p_q->a0 = 1;
//     m_cfn_p_q->a1 = (int *) malloc(sizeof(int));
//     m_cfn_p_q->a1[0] = 1;
//   }
//   else
//   {
//     m_cfn.a0 = m->cf->a0;
//     m_cfn.a1 = m->cf->a1;
//     m_cfn.a2 = m->cf->a2;
//     m_cfn.a3 = m->cf->a3;
//     jagged3_part2(m_cfn_p_q, &m_cfn, p - 1, q);
//   }
// }

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

int mesh_cfn_part3(const mesh * m, int p, int q, int i)
{
  jagged3 m_cfn;
  
  if (p == q)
    return 1;
  else
  {
    m_cfn.a0 = m->cf->a0;
    m_cfn.a1 = m->cf->a1;
    m_cfn.a2 = m->cf->a2;
    m_cfn.a3 = m->cf->a3;
    return jagged3_part3(&m_cfn, p - 1, q, i);
  }
}
