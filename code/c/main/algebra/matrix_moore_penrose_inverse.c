#include "matrix.h"

static void example_0(void)
{
  enum {d = 2, n = 3};
  double a[d * n] = {-0.5, 0, 0.5, 0, 0, 0.5};
  double b[n * d] = {0};

  puts("# a:");
  matrix_file_print(stdout, d, n, a);

  matrix_moore_penrose_inverse(b, d, n, a);
  puts("\n# b = a^*:");
  matrix_file_print(stdout, n, d, b);
}

int main(void)
{
  example_0();
}
