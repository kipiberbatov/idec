#include "mesh.h"

/* it is assumed that p > q */
void mesh_cf_part2(jagged2 * m_cf_p_q, const mesh * m, int p, int q)
{
  jagged4_part2(m_cf_p_q, m->cf, p - 1, q);
}
