#include "imath.h"
#include "simplex.h"
#include "quasi_cube.h"

/* assumes the ordering from mesh_brick() or forman() */
void quasi_cube_triangulation_node_set(
  double * s_coord, const quasi_cube * r, int s_node, int r_node)
{
  int r_dim_embedded, r_ind, s_ind, t;
  double * r_coord;
  
  r_dim_embedded = r->dim_embedded;
  r_coord = r->coord;
  r_ind = r_node * r_dim_embedded;
  s_ind = s_node * r_dim_embedded;
  for (t = 0; t < r_dim_embedded; ++t)
    s_coord[s_ind + t] = r_coord[r_ind + t];
}

void quasi_cube_triangulation_simplex_set(
  double * s_coord, const quasi_cube * r, const int * r_nodes)

{
  int p;
  
  for (p = 0; p <= r->dim; ++p)
    quasi_cube_triangulation_node_set(s_coord, r, p, r_nodes[p]);
}

double quasi_cube_triangulation_simplex_measure(
  const quasi_cube * r, const int * r_nodes)
{
  simplex s;
  double s_coord[100];
  
  s.dim_embedded = r->dim_embedded;
  s.dim = r->dim;
  quasi_cube_triangulation_simplex_set(s_coord, r, r_nodes);
  s.coord = s_coord;
  return simplex_measure(&s);
}

double quasi_cube_measure_from_triangulation(
  const quasi_cube * r, const int * r_nodes_all)
{
  int i, r_dim;
  const int * r_nodes;
  double res;
  
  r_dim = r->dim;
  res = 0;
  for (i = 0; i < imath_factorial(r_dim); ++i)
  {
    r_nodes = r_nodes_all + i * (r_dim + 1);
    res += quasi_cube_triangulation_simplex_measure(r, r_nodes);
  }
  return res;
}

static double quasi_cube_measure_0(const quasi_cube * r)
{
  return 1;
}

static double quasi_cube_measure_1(const quasi_cube * r)
{
  return quasi_cube_measure_from_triangulation(r, r_triangulation_nodes_1);
}

static double quasi_cube_measure_2(const quasi_cube * r)
{
  return quasi_cube_measure_from_triangulation(r, r_triangulation_nodes_2);
}

static double quasi_cube_measure_3(const quasi_cube * r)
{
  return quasi_cube_measure_from_triangulation(r, r_triangulation_nodes_3);
}

double quasi_cube_measure(const quasi_cube * r)
{
  int r_dim;
  
  r_dim = r->dim;
  switch (r_dim)
  {
  case 0:
    return quasi_cube_measure_0(r);
  case 1:
    return quasi_cube_measure_1(r);
  case 2:
    return quasi_cube_measure_2(r);
  case 3:
    return quasi_cube_measure_3(r);
  default:
    return 0.;
  }
}
