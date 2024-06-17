#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "diffusion_discrete.h"
#include "matrix.h"
#include "mesh.h"

static int trivially_true(const double * x)
{
  return 1;
}

static void neighbors_size(int * boundary_neighbors, int * interior_neighbors,
  int size_i, const int * neighbors, const jagged1 * boundary_nodes)
{
  int boundary_neighbors_size, interior_neighbors_size, j_local;
  
  boundary_neighbors_size = 0;
  interior_neighbors_size = 0;
  for (j_local = 0; j_local < size_i; ++j_local)
  {
    if (jagged1_member(boundary_nodes, neighbors[j_local]))
    {
      boundary_neighbors[boundary_neighbors_size] = neighbors[j_local];
      ++boundary_neighbors_size;
    }
    else
    {
      interior_neighbors[interior_neighbors_size] = neighbors[j_local];
      ++interior_neighbors_size;
    }
  }
}

/* assumes dimension 2 and convex mesh */
static void find_normals(
  double * normal,
  const double * m_coord,
  int i,
  const int * boundary_neighbors,
  const int * interior_neighbors)
{
  double p0, p1, x0, x1, x_norm, y0, y1, y_norm, z0, z1, z_norm;

  x0 = m_coord[2 * boundary_neighbors[0]] - m_coord[2 * i];
  x1 = m_coord[2 * boundary_neighbors[0] + 1] - m_coord[2 * i + 1];
  x_norm = sqrt(x0 * x0 + x1 * x1);
  x0 = x0 / x_norm;
  x1 = x1 / x_norm;
  
  y0 = m_coord[2 * boundary_neighbors[1]] - m_coord[2 * i];
  y1 = m_coord[2 * boundary_neighbors[1] + 1] - m_coord[2 * i + 1];
  y_norm = sqrt(y0 * y0 + y1 * y1);
  y0 = y0 / y_norm;
  y1 = y1 / y_norm;
  
  if (x0 * y1 - x1 * y0 < 0.0001)
  {
    p0 = m_coord[2 * interior_neighbors[0]] - m_coord[2 * i];
    p1 = m_coord[2 * interior_neighbors[0] + 1] - m_coord[2 * i + 1];
    if (p0 * x1 - p1 * x0 > 0)
    {
      normal[0] = -x1;
      normal[1] = x0;
    }
    else
    {
      normal[0] = x1;
      normal[1] = -x0;
    }
  }
  else
  {
    z0 = x0 + y0;
    z1 = x1 + y1;
    z_norm = sqrt(z0 * z0 + z1 * z1);
    normal[0] = - z0 / z_norm;
    normal[1] = - z1 / z_norm;
  }
}

void diffusion_discrete_set_neumann_rows(
  matrix_sparse * lhs,
  const mesh * m,
  const jagged1 * boundary_neumann_discrete,
  const double * pi_1)
{
  int i, i_local, m_dim_embedded, neumann_size, size_i, size_max;
  int * boundary_neighbors, * interior_neighbors, * neighbors, * neumann_nodes;
  jagged1 * boundary_nodes;
  jagged1 m_fc_0_1_i;
  jagged2 m_cf_1_0, m_fc_0_1;
  double * l, * l_inverse, * m_coord; /* matrices */
  double * coefficients; /* vector */
  double normal[3]; /* vector */
  
  m_dim_embedded = m->dim_embedded;
  m_coord = m->coord;
  mesh_fc_part2(&m_fc_0_1, m, 0, 1);
  mesh_cf_part2(&m_cf_1_0, m, 1, 0);
  
  size_max = jagged2_subset_maximal_size(boundary_neumann_discrete, &m_fc_0_1);
  
  l = (double *) malloc(sizeof(double) * m_dim_embedded * size_max);
  l_inverse = (double *) malloc(sizeof(double) * size_max * m_dim_embedded);
  coefficients = (double *) malloc(sizeof(double) * size_max);
  neighbors = (int *) malloc(sizeof(int) * size_max);
  boundary_neighbors = (int *) malloc(sizeof(int) * size_max);
  interior_neighbors = (int *) malloc(sizeof(int) * size_max);
  boundary_nodes = mesh_boundary_nodes_from_constraint(m, trivially_true);
  
  neumann_size = boundary_neumann_discrete->a0;
  neumann_nodes = boundary_neumann_discrete->a1;
  for (i_local = 0; i_local < neumann_size; ++i_local)
  {
    i = neumann_nodes[i_local];
    jagged2_part1(&m_fc_0_1_i, &m_fc_0_1, i);
    size_i = m_fc_0_1_i.a0;
    
    jagged2_node_neighbors(neighbors, &m_cf_1_0, i, &m_fc_0_1_i);
    
    mesh_boundary_node_coordinate_vectors_matrix(
      l, m, i, neighbors, &m_fc_0_1_i);
    
    matrix_moore_penrose_inverse(l_inverse, m_dim_embedded, size_i, l);
    
    neighbors_size(boundary_neighbors, interior_neighbors,
      size_i, neighbors, boundary_nodes);
    
    find_normals(normal, m_coord, i, boundary_neighbors, interior_neighbors);
    
    memset(coefficients, 0, sizeof(double) * size_i);
    matrix_times_vector(
      coefficients, size_i, m_dim_embedded, l_inverse, normal);
    double_array_multiply_with(coefficients, size_i, pi_1[i]);

    matrix_sparse_neumann_modify(lhs, i, size_i, neighbors, coefficients);
  }
  
  jagged1_free(boundary_nodes);
  free(interior_neighbors);
  free(boundary_neighbors);
  free(neighbors);
  free(coefficients);
  free(l_inverse);
  free(l);
}
