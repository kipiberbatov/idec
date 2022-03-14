#include "mesh_qc.h"

static void quasi_cube_get_coord(
  double * s_coord, const jagged1 * m_cell_nodes,
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

double * mesh_qc_vol_p(const mesh_qc * m, int p)
{
  int i, m_cn_p, m_dim, m_dim_embedded;
  int * m_cn;
  double * m_coord, * m_vol_p;
  double s_coord[100]; // 24
  quasi_cube s;
  jagged1 m_cell_nodes;
  jagged2 m_cells_nodes;
  
  m_dim_embedded = m->dim_embedded;
  m_dim = m->dim;
  m_cn = m->cn;
  m_coord = m->coord;
  m_cn_p = m_cn[p];
  s.dim_embedded = m_dim_embedded;
  s.dim = p;
  m_vol_p = (double *) malloc(m_cn_p * sizeof(double));
  /* NULL pointer check */
  if (p == 0)
  {
    for (i = 0; i < m_cn_p; ++i)
      m_vol_p[i] = 1;
    goto end;
  }
  mesh_cf_part2(&m_cells_nodes, m, p, 0);
  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_cell_nodes, &m_cells_nodes, i);
    quasi_cube_get_coord(s_coord, &m_cell_nodes, m_dim_embedded, m_coord);
    s.coord = s_coord;
    m_vol_p[i] = quasi_cube_measure(&s);
  }
end:
  return m_vol_p;
}

double ** mesh_qc_vol(const mesh_qc * m)
{
  int m_dim, p;
  double ** m_vol;
  
  m_dim = m->dim;
  m_vol = (double **) malloc((m_dim + 1) * sizeof(double *));
  /* NULL pointer check */
  for(p = 0; p <= m_dim; ++p)
  {
    m_vol[p] = mesh_qc_vol_p(m, p);
    /* NULL pointer check */
  }
  return m_vol;
}
