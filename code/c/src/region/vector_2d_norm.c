#include <math.h>

#include "vector_2d.h"

double vector_2d_norm(const double v[2])
{
  double x = v[0], y = v[1];
  return sqrt(x * x + y * y);
}
