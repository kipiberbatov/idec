#include "line_2d.h"

/* v is a vector in the perpendicular direction to l */
void line_2d_direction_90_degrees(double v[2], const struct line_2d * l)
{
  v[0] = l->x1[1] - l->x0[1];
  v[1] = l->x0[0] - l->x1[0];
}
