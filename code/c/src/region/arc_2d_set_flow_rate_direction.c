#include <math.h>

#include "arc_2d.h"
#include "line_2d.h"
#include "vector_2d.h"

void arc_2d_set_flow_rate_direction(
  struct line_2d * flow_rate_direction,
  const struct arc_2d * arc, double sign, double size)
{
  double gamma, r, v_norm, x0, y0;
  double c[2], v[2];

  x0 = arc->x0;
  y0 = arc->y0;
  r = arc->r;
  gamma = (arc->alpha + arc->beta) / 2;
  c[0] = x0 + r * cos(gamma);
  c[1] = y0 + r * sin(gamma);
  v[0] = c[0] - x0;
  v[1] = c[1] - y0;
  v_norm = vector_2d_norm(v);
  vector_2d_scalar_multiply(v, sign * size / v_norm);
  line_2d_oriented_set_from_center_and_direction(flow_rate_direction, c, v);
}
