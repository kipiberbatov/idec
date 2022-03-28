#include <stdlib.h>
#include "int.h"
#include "mesh.h"

// void mesh_cf_part2(jagged2 * m_cf_p_q, const mesh * m, int p, int q)
// {
//   if (p == q)
//   {
//     m_cf_p_q->a0 = m->cn[p];
//
//     m_cf_p_q->a1 = (int *) malloc(m_cf_p_q->a0 * sizeof(int));
//     int_array_assign_integer(m_cf_p_q->a1, m_cf_p_q->a0, 1);
//
//     m_cf_p_q->a2 = (int *) malloc(m_cf_p_q->a0 * sizeof(int));
//     int_array_assign_identity(m_cf_p_q->a2, m_cf_p_q->a0);
//   }
//   else
//     jagged4_part2(m_cf_p_q, m->cf, p - 1, q);
// }

/* it is assumed that (p > q) */
void mesh_cf_part2(jagged2 * m_cf_p_q, const mesh * m, int p, int q)
{
  jagged4_part2(m_cf_p_q, m->cf, p - 1, q);
}

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

// int mesh_cf_part4(const mesh * m, int p, int q, int i, int j_loc)
// {
//   if (p == q)
//     return i;
//   else
//     return jagged4_part4(m->cf, p - 1, q, i, j_loc);
// }
