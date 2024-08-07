#include <math.h>
#include <string.h>

#include "triangle_2d.h"

double triangle_2d_measure(const triangle_2d * p)
{
  double y00, y01, y10, y11;
  double p_x0[2], p_x1[2], p_x2[2];

  memcpy(p_x0, p->x0, sizeof(double) * 2);
  memcpy(p_x1, p->x1, sizeof(double) * 2);
  memcpy(p_x2, p->x2, sizeof(double) * 2);
  y00 = p_x1[0] - p_x0[0];
  y01 = p_x1[1] - p_x0[1];
  y10 = p_x2[0] - p_x0[0];
  y11 = p_x2[1] - p_x0[1];
  return fabs(y00 * y11 - y01 * y10) / 2;
}
