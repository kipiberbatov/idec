#include <stdlib.h>
#include "mesh.h"
#include "list.h"

void mesh_cf_part2(jagged2 * m_cf_p_q, const mesh * m, int p, int q)
{
  int i;
  if (p == q)
  {
    m_cf_p_q->a0 = m->cn[p];
    
    m_cf_p_q->a1 = (int *) malloc(m_cf_p_q->a0 * sizeof(int));
    for (i = 1; i < m_cf_p_q->a0; ++i)
      m_cf_p_q->a1[i] = 1;
    
    m_cf_p_q->a2 = (int *) malloc(m_cf_p_q->a0 * sizeof(int));
    for (i = 1; i < m_cf_p_q->a0; ++i)
      m_cf_p_q->a1[i] = i;
  }
  else
    jagged4_part2(m_cf_p_q, m->cf, p - 1, q);
}

void mesh_cf_part3(jagged1 * m_cf_p_q_i, const mesh * m, int p, int q, int i)
{
  if (p == q)
  {
    m_cf_p_q_i->a0 = 1;
    m_cf_p_q_i->a1 = m->c + list_sum(m->cn, 0, p) + i;
  }
  else
    jagged4_part3(m_cf_p_q_i, m->cf, p - 1, q, i);
}

int mesh_cf_part4(const mesh * m, int p, int q, int i, int j_loc)
{
  if (p == q)
    return i;
  else
    return jagged4_part4(m->cf, p - 1, q, i, j_loc);
}
