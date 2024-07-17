#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "diffusion_discrete.h"
#include "matrix.h"
#include "mesh.h"

/* TODO: memory allocation checks */
void diffusion_discrete_set_neumann_rows(
  matrix_sparse * lhs,
  const mesh * m,
  const jagged1 * boundary_neumann_discrete,
  const double * pi_1)
{
  int d, i, i_local, m_dim_embedded, neumann_size, size_i, size_max,
      size_max_dm1;
  int * neighbors, * neumann_nodes;
  jagged1 * boundary_hyperfaces;
  jagged1 m_fc_0_1_i;
  jagged2 m_cf_1_0, m_cf_dm1_0, m_fc_0_1, m_fc_0_dm1;
  double m_size;
  double * l, * l_inverse; /* matrices */
  double * hyperface_normals; /* list of vectors */
  double * coefficients; /* vector */
  double normal[3]; /* vector */
  
  d = m->dim;
  m_dim_embedded = m->dim_embedded;
  mesh_cf_part2(&m_cf_1_0, m, 1, 0);
  mesh_fc_part2(&m_fc_0_1, m, 0, 1);
  mesh_cf_part2(&m_cf_dm1_0, m, d - 1, 0);
  mesh_fc_part2(&m_fc_0_dm1, m, 0, d - 1);
  m_size = mesh_size(m);

  boundary_hyperfaces = mesh_boundary_hyperfaces(m);
  
  size_max_dm1 = jagged2_subset_maximal_size(
    boundary_neumann_discrete, &m_fc_0_dm1);
  hyperface_normals = (double *) malloc(sizeof(double) * d * size_max_dm1);

  size_max = jagged2_subset_maximal_size(boundary_neumann_discrete, &m_fc_0_1);
  l = (double *) malloc(sizeof(double) * m_dim_embedded * size_max);
  l_inverse = (double *) malloc(sizeof(double) * size_max * m_dim_embedded);
  coefficients = (double *) malloc(sizeof(double) * size_max);
  neighbors = (int *) malloc(sizeof(int) * size_max);
  
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
    
    mesh_node_normal(normal, hyperface_normals,
      m, boundary_hyperfaces, &m_cf_dm1_0, &m_fc_0_dm1, m_size, i);

    /* $coefficients = pi_1[i] * (l_inverse . normal)$ */
    memset(coefficients, 0, sizeof(double) * size_i);
    matrix_times_vector(
      coefficients, size_i, m_dim_embedded, l_inverse, normal);
    double_array_multiply_with(coefficients, size_i, pi_1[i]);
    
    /*
    fputs("x = ", stderr);
    double_array_file_print(stderr, d, m->coord + d * i, "--curly");
    fputs(", n = ", stderr);
    double_array_file_print(stderr, d, normal, "--curly");
    fputs(", c = ", stderr);
    double_array_file_print(stderr, size_i, coefficients, "--curly");
    putc('\n', stderr);
    */

    matrix_sparse_neumann_modify(lhs, i, size_i, neighbors, coefficients);
  }
  
  jagged1_free(boundary_hyperfaces);
  free(hyperface_normals);
  free(neighbors);
  free(coefficients);
  free(l_inverse);
  free(l);
}
