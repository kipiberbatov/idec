#include <stdlib.h>
#include "imath.h"
#include "list.h"
#include "mesh_brick.h"

static void array_set_to_integer(int * a, int n, int c)
{
  int i;
  
  for (i = 0; i < n; ++ i)
    a[i] = c;
}

double * mesh_brick_coord(
  int m_dim, int m_cn_0, const double * brick_lengths, const int * n)
{
  int cells_ind, cells_total, global_ind, p;
  int cells[MAX_DIM], n_bar[MAX_DIM];
  double units[MAX_DIM];
  double * coord;
  
  coord = (double *) malloc(m_cn_0 * m_dim * sizeof(double));
  /* NULL pointer check */
  for (p = 0; p < m_dim; ++p)
    units[p] = brick_lengths[p] / ((double) n[p]);
  for (p = 0; p < m_dim; ++p)
    n_bar[p] = n[p] + 1;
  array_set_to_integer(cells, m_dim, 0);
  cells_total = list_product(n_bar, 0, m_dim);
  global_ind = 0;
  for (cells_ind = 0; cells_ind < cells_total; ++cells_ind)
  {
    for (p = 0; p < m_dim; ++p)
      coord[global_ind + p] = ((double) cells[p]) * units[p];
    global_ind += m_dim;
    if (cells_ind < cells_total - 1)
      imath_cartesian_product_next(cells, m_dim, n_bar);
  }
  return coord;
}
