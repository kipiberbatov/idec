#include <errno.h>
#include <stdlib.h>
#include "int.h"
#include "mesh_brick_private.h"

void mesh_brick_coord(double * m_coord, int m_dim, 
                      const double * brick_lengths, const int * n)
{
  int cells_ind, cells_total, ind, p;
  int cells[MAX_DIM], n_bar[MAX_DIM];
  double units[MAX_DIM];
  
  for (p = 0; p < m_dim; ++p)
    units[p] = brick_lengths[p] / ((double) n[p]);
  
  for (p = 0; p < m_dim; ++p)
    n_bar[p] = n[p] + 1;
  
  int_array_assign_constant(cells, m_dim, 0);
  cells_total = int_array_total_product(m_dim, n_bar);
  
  ind = 0;
  for (cells_ind = 0; cells_ind < cells_total; ++cells_ind)
  {
    for (p = 0; p < m_dim; ++p)
      m_coord[ind + p] = ((double) cells[p]) * units[p];
    ind += m_dim;
    if (cells_ind < cells_total - 1)
      int_array_cartesian_product_next(cells, m_dim, n_bar);
  }
}
