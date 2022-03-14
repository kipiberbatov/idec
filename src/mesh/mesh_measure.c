#include <stdlib.h>
#include "list.h"
#include "mesh.h"
#include "quasi_cube.h"
#include "simplex.h"

/* finds the volumes of a simplicial mesh or of a quasi-cubical mesh */

/*
typedef struct polytope
{
  int dim_embedded;
  int dim;
  double * coord;
  int type;
} polytope;
*/

static void polytope_coord(double * s_coord, const jagged1 * m_cell_nodes,
                           int m_dim_embedded, const double * m_coord)
{
  int m_cell_nodes_a0, node, t, tmp1, tmp2;
  int * m_cell_nodes_a1;
  
  m_cell_nodes_a0 = m_cell_nodes->a0;
  m_cell_nodes_a1 = m_cell_nodes->a1;
  
  for (node = 0; node < m_cell_nodes_a0; ++node)
  {
    tmp1 = node * m_dim_embedded;
    tmp2 = m_cell_nodes_a1[node] * m_dim_embedded;
    for (t = 0; t < m_dim_embedded; ++t)
      s_coord[tmp1 + t] = m_coord[tmp2 + t];
  }
}

double * mesh_measure_simplex(const mesh * m)
{
  int i, ind, m_dim, m_dim_embedded, m_vol_size, p;
  int * m_cn;
  double * m_coord, * m_vol;
  double s_coord[24];
  jagged1 m_cell_nodes;
  simplex s;
  
  m_dim = m->dim;
  m_dim_embedded = m->dim_embedded;
  m_cn = m->cn;
  m_coord = m->coord;
  
  m_vol_size = list_sum(m_cn, 0, m_dim + 1);
  m_vol = (double *) malloc(m_vol_size * sizeof(double));
  /* NULL pointer check */
  
  s.dim_embedded = m_dim_embedded;
  
  ind = 0;
  for (p = 0; p <= m_dim; ++p)
  {
    s.dim = p;
    for (i = 0; i < m_cn[p]; ++i)
    {
      mesh_cf_part3(&m_cell_nodes, m, p, 0, i);
      polytope_coord(s_coord, &m_cell_nodes, m_dim_embedded, m_coord);
      s.coord = s_coord;
      m_vol[ind] = simplex_measure(&s);
      ++ind;
    }
  }
  
  return m_vol;
}

double * mesh_measure_quasi_cube(const mesh * m)
{
  int i, ind, m_dim, m_dim_embedded, m_vol_size, p;
  int * m_cn;
  double * m_coord, * m_vol;
  double s_coord[24];
  jagged1 m_cell_nodes;
  quasi_cube s;
  
  m_dim = m->dim;
  m_dim_embedded = m->dim_embedded;
  m_cn = m->cn;
  m_coord = m->coord;
  
  m_vol_size = list_sum(m_cn, 0, m_dim + 1);
  m_vol = (double *) malloc(m_vol_size * sizeof(double));
  /* NULL pointer check */
  
  s.dim_embedded = m_dim_embedded;
  
  ind = 0;
  for (p = 0; p <= m_dim; ++p)
  {
    s.dim = p;
    for (i = 0; i < m_cn[p]; ++i)
    {
      mesh_cf_part3(&m_cell_nodes, m, p, 0, i);
      polytope_coord(s_coord, &m_cell_nodes, m_dim_embedded, m_coord);
      s.coord = s_coord;
      m_vol[ind] = quasi_cube_measure(&s);
      ++ind;
    }
  }
  
  return m_vol;
}
