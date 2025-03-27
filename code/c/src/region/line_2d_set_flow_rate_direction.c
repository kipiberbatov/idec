#include "line_2d.h"
#include "vector_2d.h"

void line_2d_set_flow_rate_direction(
  struct line_2d * flow_rate_direction,
  const struct line_2d * line, double sign, double size)
{
  double v_norm;
  double c[2], v[2];

  line_2d_midpoint(c, line);
  line_2d_direction_90_degrees(v, line);
  v_norm = vector_2d_norm(v);
  vector_2d_scalar_multiply(v, sign * size / v_norm);
  line_2d_oriented_set_from_center_and_direction(flow_rate_direction, c, v);
}
