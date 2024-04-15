#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "diffusion_discrete.h"
#include "matrix.h"
#include "mesh.h"

static int size_max_calculate(
  const jagged1 * boundary_neumann_discrete,
  const jagged2 * m_fc_0_1)
{
  int i, i_local, neumann_size, size_i, size_max;
  int * neumann_nodes;
  jagged1 m_fc_0_1_i;
    
  neumann_size = boundary_neumann_discrete->a0;
  neumann_nodes = boundary_neumann_discrete->a1;
  size_max = 0;
  
  for (i_local = 0; i_local < neumann_size; ++i_local)
  {
    i = neumann_nodes[i_local];
    jagged2_part1(&m_fc_0_1_i, m_fc_0_1, i);
    size_i = m_fc_0_1_i.a0;
    if (size_i > size_max)
      size_max = size_i;
  }
  return size_max;
}

static int jagged1_couple_other_object(const jagged1 * arr, int i)
{
  if (arr->a1[0] == i)
    return arr->a1[1];
  return arr->a1[0];
}

static void neighbors_calculate(
  int * neighbors,
  const jagged2 * m_cf_1_0,
  int i,
  int size_i,
  const int * values_i)
{
  int j, j_local;
  jagged1 m_cf_1_0_j;
  
  for (j_local = 0; j_local < size_i; ++ j_local)
  {
    j = values_i[j_local];
    jagged2_part1(&m_cf_1_0_j, m_cf_1_0, j);
    neighbors[j_local] = jagged1_couple_other_object(&m_cf_1_0_j, i);
  }
}

static void line_vectors_matrix_calculate(
  double * l,
  const int * neighbors,
  int m_dim_embedded,
  const double * m_coord,
  const double * m_coord_i,
  int size_i,
  const int * values_i
)
{
  int i0, j_local, s;
  double * l_j_local;
  const double * m_coord_i0;
  
  for (j_local = 0; j_local < size_i; ++ j_local)
  {
    i0 = neighbors[j_local];
    m_coord_i0 = m_coord + m_dim_embedded * i0;
    l_j_local = l + m_dim_embedded * j_local;
    for (s = 0; s < m_dim_embedded; ++s)
      l_j_local[s] = m_coord_i[s] - m_coord_i0[s];
  }
}

/* works only for a meshing of the unit square */
void normals_calculate(double * normal, const double * m_coord_i)
{
  const double * x = m_coord_i;

  if ((x[1] == 0. || x[1] == 1.) && x[0] != 0. && x[0] != 1.)
  {
    normal[0] = 0.;
    if (x[1] == 0.)
      normal[1] = -1.;
    else
      normal[1] = 1.;
  }
  else if ((x[0] == 0. || x[0] == 1.) && x[1] != 0. && x[1] != 0.)
  {
    normal[1] = 0.;
    if (x[0] == 0.)
      normal[0] = -1.;
    else
      normal[0] = 1.;
  }
}

static void global_matrix_modify(
  matrix_sparse * lhs,
  int i,
  int size_i,
  const int * neighbors,
  const double * coefficients)
{
  int i0, j_local;
  double * position;
  
  for (j_local = 0; j_local < size_i; ++j_local)
  {
    i0 = neighbors[j_local];
    position = matrix_sparse_part_pointer(lhs, i, i0);
    *position = -coefficients[j_local];
  }
  position = matrix_sparse_part_pointer(lhs, i, i);
  *position = 0;
  for (j_local = 0; j_local < size_i; ++j_local)
    *position = coefficients[j_local];
}

void diffusion_discrete_set_neumann_rows(
  matrix_sparse * lhs,
  const mesh * m,
  const jagged1 * boundary_neumann_discrete,
  const double * pi_1)
{
  int i, i_local, m_dim_embedded, neumann_size, size_i, size_max;
  int * neighbors, * neumann_nodes, * values_i;
  jagged1 m_fc_0_1_i;
  jagged2 m_cf_1_0, m_fc_0_1;
  double * m_coord, * m_coord_i;
  double * l, * l_inverse; // matrices
  double * coefficients; // vector
  double normal[2]; // vector
  
  m_dim_embedded = m->dim_embedded;
  m_coord = m->coord;
  mesh_fc_part2(&m_fc_0_1, m, 0, 1);
  mesh_cf_part2(&m_cf_1_0, m, 1, 0);
  
  size_max = size_max_calculate(boundary_neumann_discrete, &m_fc_0_1);
  
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
    values_i = m_fc_0_1_i.a1;
    m_coord_i = m_coord + i * m_dim_embedded;
    
    neighbors_calculate(neighbors, &m_cf_1_0, i, size_i, values_i);
    
    line_vectors_matrix_calculate(
      l, neighbors, m_dim_embedded, m_coord, m_coord_i, size_i, values_i);
    
    matrix_moore_penrose_inverse(l_inverse, m_dim_embedded, size_i, l);
    
    normals_calculate(normal, m_coord_i);
    
    memset(coefficients, 0, sizeof(double) * size_i);
    matrix_times_vector(
      coefficients, size_i, m_dim_embedded, l_inverse, normal);
    double_array_multiply_with(coefficients, size_i, pi_1[i]);

    global_matrix_modify(lhs, i, size_i, neighbors, coefficients);
  }
  
  free(neighbors);
  free(coefficients);
  free(l_inverse);
  free(l);
}
