#include <stdlib.h>
#include "int.h"
#include "mesh.h"

/* it is assumed that (p > q) */
void mesh_fc_part2(jagged2 * m_fc_q_p, const mesh * m, int q, int p)
{
  jagged4_part2(m_fc_q_p, m->fc, q, p - q - 1);
}
