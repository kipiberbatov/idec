#include <errno.h>
#include <stdlib.h>

#include "matrix.h"
#include "mesh.h"

double * mesh_boundary_neumann_coefficients(const mesh * m, int i)
{
  int m_dim_embedded, size;
  jagged1 m_fc_0_1_i;
  jagged2 m_fc_0_1;
  double * l, * l_inverse; // matrices
  double * result; // vector
  double normal[2]; // vector

  m_dim_embedded = m->dim_embedded;
  mesh_fc_part2(&m_fc_0_1, m, 0, 1);
  jagged2_part1(&m_fc_0_1_i, &m_fc_0_1, i);

  size = m_fc_0_1_i.a0;

  l = mesh_boundary_node_vectors_matrix(m, i);

  l_inverse = (double *) malloc(sizeof(double) * size * m_dim_embedded);
  // NULL
  result = (double *) malloc(sizeof(double) * size);
  // NULL

  matrix_moore_penrose_inverse(l_inverse, m_dim_embedded, size, l);
  mesh_boundary_node_normal(normal, m, i);
  matrix_times_vector(result, size, m_dim_embedded, l_inverse, normal);

  // free(l_inverse);
  // free(l);
  return result;
}
