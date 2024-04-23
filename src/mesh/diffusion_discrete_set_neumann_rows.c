#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "diffusion_discrete.h"
#include "matrix.h"
#include "mesh.h"

void diffusion_discrete_set_neumann_rows(
  matrix_sparse * lhs,
  const mesh * m,
  const jagged1 * boundary_neumann_discrete,
  const double * pi_1)
{
  int i, i_local, m_dim_embedded, neumann_size, size_i, size_max;
  int * neighbors, * neumann_nodes;
  jagged1 m_fc_0_1_i;
  jagged2 m_cf_1_0, m_fc_0_1;
  double * l, * l_inverse; /* vector */
  double * coefficients; /* vector */
  double normal[3]; /* vector */
  
  m_dim_embedded = m->dim_embedded;
  mesh_fc_part2(&m_fc_0_1, m, 0, 1);
  mesh_cf_part2(&m_cf_1_0, m, 1, 0);
  
  size_max = jagged2_subset_maximal_size(boundary_neumann_discrete, &m_fc_0_1);
  
  l = (double *) malloc(sizeof(double) * m_dim_embedded * size_max);
  l_inverse = (double *) malloc(sizeof(double) * size_max * m_dim_embedded);
  coefficients = (double *) malloc(sizeof(double) * size_max);
  neighbors = (int *) malloc(sizeof(double) * size_max);
  
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
    
    mesh_boundary_node_normal(normal, m, i);
    
    memset(coefficients, 0, sizeof(double) * size_i);
    matrix_times_vector(
      coefficients, size_i, m_dim_embedded, l_inverse, normal);
    double_array_multiply_with(coefficients, size_i, pi_1[i]);

    matrix_sparse_neumann_modify(lhs, i, size_i, neighbors, coefficients);
  }
  
  free(neighbors);
  free(coefficients);
  free(l_inverse);
  free(l);
}
