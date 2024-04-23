#include <string.h>
#include <math.h>

#include "line_2d.h"

double line_2d_measure(const line_2d * p)
{
  double y0, y1;
  double p_x0[2], p_x1[2];
  
  memcpy(p_x0, p->x0, sizeof(double) * 2);
  memcpy(p_x1, p->x1, sizeof(double) * 2);
  y0 = p_x1[0] - p_x0[0];
  y1 = p_x1[1] - p_x0[1];
  return sqrt(y0 * y0 + y1 * y1);
}
