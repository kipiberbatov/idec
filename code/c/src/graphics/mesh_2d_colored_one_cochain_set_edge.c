#include <math.h>

#include "mesh_2d_colored_one_cochain.h"

void mesh_2d_colored_one_cochain_set_edge(
  mesh_2d_colored_edge * edge,
  const mesh_2d_colored_one_cochain * c,
  int i,
  int * cf_1_0_i)
{
  double denominator, v0, v1, v_norm, z0, z1;
  double * e0, * e1;

  denominator = c->max_value - c->min_value;
  e0 = c->coordinates + 2 * cf_1_0_i[0];
  e1 = c->coordinates + 2 * cf_1_0_i[1];
  v0 = e1[1] - e0[1];
  v1 = e0[0] - e1[0];
  v_norm = sqrt(v0 * v0 + v1 * v1);
  v0 = (v0 / v_norm) * edge->point_size;
  v1 = (v1 / v_norm) * edge->point_size;
  z0 = (e0[0] + e1[0]) / 2;
  z1 = (e0[1] + e1[1]) / 2;
  if (c->bd_1[2 * i] * c->values[i] < 0)
  {
    edge->coordinates_0[0] = z0 - v0;
    edge->coordinates_0[1] = z1 - v1;
    edge->coordinates_1[0] = z0 + v0;
    edge->coordinates_1[1] = z1 + v1;
  }
  else
  {
    edge->coordinates_0[0] = z0 + v0;
    edge->coordinates_0[1] = z1 + v1;
    edge->coordinates_1[0] = z0 - v0;
    edge->coordinates_1[1] = z1 - v1;
  }
  if (denominator == 0.)
    edge->relative_value = 0.;
  else
    edge->relative_value = (fabs(c->values[i]) - c->min_value) / denominator;
}
