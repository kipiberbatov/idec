#include "matrix.h"

static void example_2()
{
  double a[4] = {1., 2., 3., 4.};
  printf("det({{1, 3}, {2, 4}}) = %g\n", matrix_determinant(2, a));
}

static void example_3()
{
  double a[9] = {1., 2., 3., 4., 5., 6., 7., 8., 0.};
  printf("det({{1, 4, 7}, {2, 5, 8}, {3, 6, 0}}) = %g\n",
    matrix_determinant(3, a));
}

int main(void)
{
  puts("# Determiant in 2D:");
  example_2();
  puts("");
  puts("# Determiant in 3D:");
  example_3();
}
