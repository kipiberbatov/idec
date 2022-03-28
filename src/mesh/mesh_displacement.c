#include <stdlib.h>
#include "mesh.h"

static void point_difference(
  double * res, int d, const double * a, const double * b)
{
  int i;
  
  for (i = 0; i < d; ++i)
    res[i] = b[i] - a[i];
}

static void vector_scalar_multiply_by(double * a, int d, double lambda)
{
  int i;
  
  for (i = 0; i < d; ++i)
    a[i] *= lambda;
}

static void vector_add_to(double * a, int d, const double * b)
{
  int i;
  
  for (i = 0; i < d; ++i)
    a[i] += b[i];
}

double ** mesh_displacement(
  const mesh * m, const matrix_sparse * m_bd_0, const double * u)
{
  int i, j, j_loc, m_cn_0, m_dim_embedded;
  double sign;
  double tmp[MAX_DIM];
  double * m_coord;
  double ** res;
  jagged1 edges, edge_nodes;
  
  m_dim_embedded = m->dim_embedded;
  m_cn_0 = m->cn[0];
  m_coord = m->coord;
  res = (double **) calloc(m_cn_0, sizeof(double *));
  /* NULL pointer check */
  for (i = 0; i < m_cn_0; ++i)
  {
    res[i] = (double *) calloc(m_dim_embedded, sizeof(double));
    /* NULL pointer check */
  }
  for (i = 0; i < m_cn_0; ++i)
  {
    mesh_fc_part3(&edges, m, 0, 1, i);
    for (j_loc = 0; j_loc < edges.a0; ++j_loc)
    {
      j = edges.a1[j_loc];
      mesh_cf_part3(&edge_nodes, m, 1, 0, j);
      sign = matrix_sparse_part(m_bd_0, i, j);
      point_difference(tmp, m_dim_embedded, 
                       m_coord + m_dim_embedded * edge_nodes.a1[0],
                       m_coord + m_dim_embedded * edge_nodes.a1[1]);
      vector_scalar_multiply_by(tmp, m_dim_embedded, - sign * u[j]);
      vector_add_to(res[i], m_dim_embedded, tmp);
    }
  }
  return res;
}
  