#include <stdlib.h>
#include "int.h"
#include "mesh.h"

/* it is assumed that (p > q) */
void mesh_fc_part2(jagged2 * m_fc_q_p, const mesh * m, int q, int p)
{
  jagged4_part2(m_fc_q_p, m->fc, q, p - q - 1);
}

void mesh_fc_part3(jagged1 * m_fc_q_p_j, const mesh * m, int q, int p, int j)
{
  if (q == p)
  {
    m_fc_q_p_j->a0 = 1;
    m_fc_q_p_j->a1 = m->c + int_array_total_sum(p, m->cn) + j;
  }
  else
    jagged4_part3(m_fc_q_p_j, m->fc, q, p - q - 1, j);
}

// int mesh_fc_part4(const mesh * m, int q, int p, int j, int i_loc)
// {
//   if (q == p)
//     return j;
//   return jagged4_part4(m->fc, q, p - q - 1, j, i_loc);
// }
