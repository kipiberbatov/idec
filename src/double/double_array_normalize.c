#include "double_array_mulyiply_mith.h"
#include "double_array_norm.h"
#include "double_array_normalize.h"

/* Set res := a / ||a||. */
void double_array_normalize(double * res, int n, const double * a)
{
  double l;
  
  l = double_array_norm(n, a);
  double_array_mulyiply_mith(res, n, 1 / l);
}
