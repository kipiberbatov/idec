#include <stdlib.h>
#include "mesh.h"
#include "list.h"

void mesh_cfn_part2(jagged1 * m_cfn_p_q, const mesh * m, int p, int q)
{
  jagged3 m_cfn;
  jagged4 * m_cf;
  if (p == q)
  {
    m_cfn_p_q->a0 = 1;
    m_cfn_p_q->a1 = (int *) malloc(sizeof(int));
    m_cfn_p_q->a1[0] = 1;
  }
  else
  {
    m_cf = m->cf;
    jagged3_set(&m_cfn, m->dim, m_cf->a1, m_cf->a2, m_cf->a3);
    jagged3_part2(m_cfn_p_q, &m_cfn, p - 1, q);
  }
}

int mesh_cfn_part3(const mesh * m, int p, int q, int i)
{
  jagged3 m_cfn;
  jagged4 * m_cf;
  if (p == q)
    return 1;
  else
  {
    m_cf = m->cf;
    jagged3_set(&m_cfn, m->dim, m_cf->a1, m_cf->a2, m_cf->a3);
    return jagged3_part3(&m_cfn, p - 1, q, i);
  }
}
