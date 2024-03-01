#include <math.h>

#include "double_array_dot_product.h"
#include "double_array_norm.h"

/* Find ||a||. */
double double_array_norm(int n, const double * a)
{
  double length_square;
  
  length_square = double_array_dot_product(n, a, a);
  return sqrt(length_square);
}
