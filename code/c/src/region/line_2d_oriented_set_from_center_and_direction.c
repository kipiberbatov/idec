#include "line_2d.h"

void line_2d_oriented_set_from_center_and_direction(
  struct line_2d * flow_rate_direction, const double c[2], const double v[2])
{
  double c0 = c[0], c1 = c[1], v0 = v[0], v1 = v[1];

  flow_rate_direction->x0[0] = c0 - v0 / 2;
  flow_rate_direction->x0[1] = c1 - v1 / 2;
  flow_rate_direction->x1[0] = c0 + v0 / 2;
  flow_rate_direction->x1[1] = c1 + v1 / 2;
}
