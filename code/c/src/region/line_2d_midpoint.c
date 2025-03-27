#include "line_2d.h"

void line_2d_midpoint(double c[2], const struct line_2d * line)
{
  c[0] = (line->x0[0] + line->x1[0]) / 2;
  c[1] = (line->x0[1] + line->x1[1]) / 2;
}
