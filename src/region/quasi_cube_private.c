#include "int.h"
#include "simplex.h"
#include "quasi_cube_private.h"

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
  int i, r_dim, r_dim_factorial;
  const int * r_nodes;
  double res;

  r_dim = r->dim;
  r_dim_factorial = int_factorial(r_dim);
  res = 0;
  for (i = 0; i < r_dim_factorial; ++i)
  {
    r_nodes = r_nodes_all + i * (r_dim + 1);
    res += quasi_cube_triangulation_simplex_measure(r, r_nodes);
  }
  return res;
}
