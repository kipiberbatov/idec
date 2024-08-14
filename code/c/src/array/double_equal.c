#include "double.h"

int double_equal(double x, double y, double tolerance)
{
  double z = x - y;
  return z < tolerance && -z < tolerance;
}
