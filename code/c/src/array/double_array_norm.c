#include <math.h>
#include "double.h"

double double_array_norm(int d, const double * a)
{
  double length_square;

  length_square = double_array_dot_product(d, a, a);
  return sqrt(length_square);
}
