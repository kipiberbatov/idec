#include "mesh_qc.h"
#include "list.h"

static double vec_sparse_part(const vec_sparse * a, int ind)
{
  int i;
  jagged1 a_positions;
  
  a_positions.a0 = a->nzmax;
  a_positions.a1 = a->p;
  i = list_position(&a_positions, ind);
  return ((i == -1) ? 0. : a->x[i]);
}

double mesh_qc_integrate(const mesh_qc * m, const double * m_vol_m_dim,
                         const vec_sparse * a)
{
  int i, j_loc, m_dim, a_ind;
  int * m_cn;
  double sum, sum_loc;
  jagged1 m_cell_nodes;
  jagged2 m_cells_nodes;
  
  m_dim = m->dim;
  m_cn = m->cn;
  mesh_cf_part2(&m_cells_nodes, m, m_dim, 0);
  sum = 0.;
  for (i = 0; i < m_cn[m_dim]; ++i)
  {
    jagged2_part1(&m_cell_nodes, &m_cells_nodes, i);
    sum_loc = 0.;
    for (j_loc = 0; j_loc < m_cell_nodes.a0; ++j_loc)
    {
      a_ind = (m_cell_nodes.a1)[j_loc];
      sum_loc += vec_sparse_part(a, a_ind);
    }
    sum += m_vol_m_dim[i] * sum_loc / ((double) m_cell_nodes.a0);
  }
  return sum;
}
