#include "double.h"
#include "matrix.h"

static void example_0(void)
{
  enum {d = 2, n = 3};
  const double a[n * d] = {1., 3., 5., 2., 4. ,6.};
  const double x[d] = {3, 4};
  double b[n] = {0};

  puts("# a:");
  matrix_file_print(stdout, d, n, a);

  puts("\n# x:");
  double_array_file_print(stdout, d, x, "--raw");

  matrix_times_vector(b, n, d, a, x);
  puts("\n# b = a x:");
  double_array_file_print(stdout, n, b, "--raw");
}

int main(void)
{
  example_0();
}
