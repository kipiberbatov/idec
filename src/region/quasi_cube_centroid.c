#include "double.h"
#include "int.h"
#include "quasi_cube_private.h"
#include "simplex.h"

/* assumes the ordering from mesh_brick() or forman() */

static void quasi_cube_triangulation_simplex_centroid(
  double * s_centroid, const quasi_cube * r, const int * r_nodes)
{
  simplex s;
  double s_coord[24];

  s.dim_embedded = r->dim_embedded;
  s.dim = r->dim;
  quasi_cube_triangulation_simplex_set(s_coord, r, r_nodes);
  s.coord = s_coord;
  simplex_centroid(s_centroid, &s);
}

static void quasi_cube_centroid_from_triangulation(
  double * r_centroid, const quasi_cube * r, const int * r_nodes_all)
{
  int i, r_dim, r_dim_embedded, r_dim_factorial;
  const int * r_nodes;
  double s_centroid[3];
  double r_measure, s_measure;

  r_dim_embedded = r->dim_embedded;
  r_dim = r->dim;
  double_array_assign_constant(r_centroid, r_dim_embedded, 0);
  r_dim_factorial = int_factorial(r_dim);
  r_measure = 0;
  for (i = 0; i < r_dim_factorial; ++i)
  {
    r_nodes = r_nodes_all + i * (r_dim + 1);
    double_array_assign_constant(s_centroid, r_dim_embedded, 0);
    quasi_cube_triangulation_simplex_centroid(s_centroid, r, r_nodes);
    s_measure = quasi_cube_triangulation_simplex_measure(r, r_nodes);
    r_measure += s_measure;
    double_array_multiply_with(s_centroid, r_dim_embedded, s_measure);
    double_array_add_to(r_centroid, r_dim_embedded, s_centroid);
  }
  double_array_multiply_with(r_centroid, r_dim_embedded, 1 / r_measure);
}

void quasi_cube_centroid(double * r_centroid, const quasi_cube * r)
{
  int r_dim;

  r_dim = r->dim;
  switch (r_dim)
  {
  case 0:
    quasi_cube_centroid_from_triangulation(
      r_centroid, r, quasi_cube_triangulation_nodes_0);
    return;
  case 1:
    quasi_cube_centroid_from_triangulation(
      r_centroid, r, quasi_cube_triangulation_nodes_1);
    return;
  case 2:
    quasi_cube_centroid_from_triangulation(
      r_centroid, r, quasi_cube_triangulation_nodes_2);
    return;
  case 3:
    quasi_cube_centroid_from_triangulation(
      r_centroid, r, quasi_cube_triangulation_nodes_3);
    return;
  default:
    return;
  }
}
