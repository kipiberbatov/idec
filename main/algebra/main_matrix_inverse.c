#include "matrix.h"

static void example_2()
{
  enum {d = 2};
  double a[d * d] = {1., 2., 3., 4.};
  double b[d * d] = {0};

  puts("a :");
  matrix_file_print(stdout, d, d, a);

  matrix_inverse(b, d, a);
  puts("\nb = a^{-1}:");
  matrix_file_print(stdout, d, d, b);
}

static void example_3()
{
  enum {d = 3};
  double a[d * d] = {1., 2., 3., 4., 5., 6., 7., 8., 0.};
  double b[d * d] = {0};

  puts("a :");
  matrix_file_print(stdout, d, d, a);

  matrix_inverse(b, d, a);
  puts("\nb = a^{-1} :");
  matrix_file_print(stdout, d, d, b);
}

int main(void)
{
  example_2();
  puts("\n");
  example_3();
}
