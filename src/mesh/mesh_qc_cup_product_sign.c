#include "mesh_qc_private.h"

/* r = p + q,
 * cc[r, k] = sign * 2^r * (polytope_sum(cc[p, i], cc[q, j])).
 * cup_product(cc[p, i], cc[q, j]) = (sign / 2^r) * cc[r, k].
 */
double mesh_qc_cup_product_sign(
  matrix_sparse ** m_bd, int node, int p, int i, int q, int j, int r, int k)
{
  if (p == 1)
    return matrix_sparse_part(m_bd[0], node, i) *
           matrix_sparse_part(m_bd[r - 1], j, k);
  if (q == 1)
    return matrix_sparse_part(m_bd[0], node, j) *
           matrix_sparse_part(m_bd[r - 1], i, k);
  return 1.;
}
