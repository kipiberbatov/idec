#include <math.h>

#include "points_array_minimal_distance.h"

static double double_square(double x) { return x * x; }

/* The most straightforward but O(n^2) method */
double points_array_minimal_distance(int n, const double * p)
{
  int i, j;
  double p_i_x, p_i_y, p_j_x, p_j_y;
  double result_squared, tmp_squared;

  result_squared = double_square(p[0] - p[2]) + double_square(p[1] - p[3]);

  for (i = 0; i < n; ++i)
  {
    p_i_x = p[2 * i];
    p_i_y = p[2 * i + 1];
    for (j = i + 1; j < n; ++j)
    {
      p_j_x = p[2 * j];
      p_j_y = p[2 * j + 1];
      tmp_squared = double_square(p_i_x - p_j_x) + double_square(p_i_y - p_j_y);
      if (tmp_squared < result_squared)
        result_squared = tmp_squared;
    }
  }
  return sqrt(result_squared);
}
