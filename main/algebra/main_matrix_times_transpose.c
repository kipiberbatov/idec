#include "matrix.h"

static void example_0(void)
{
  enum {d = 2, n = 3};
  double a[d * n] = {-0.5, 0, 0.5, 0, 0, 0.5};
  double b[d * d] = {0};

  puts("# a:");
  matrix_file_print(stdout, d, n, a);
  matrix_times_transpose(b, d, n, a);

  puts("\n# b = a a^T:");
  matrix_file_print(stdout, d, d, b);
}

int main(void)
{
  example_0();
}
