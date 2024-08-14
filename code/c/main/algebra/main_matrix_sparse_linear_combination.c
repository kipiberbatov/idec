#include <errno.h>
#include <stdlib.h>
#include "matrix_sparse.h"

static void matrix_sparse_linear_combination_file_print(
  FILE * out, const char * a_name, const char * a_format, const char * b_name,
  const char * b_format, double alpha, double beta, const char * out_format)
{
  matrix_sparse * a, * b, * c;

  a = matrix_sparse_file_scan_by_name(a_name, a_format);
  if (errno)
  {
    perror("Cannot scan the first matrix");
    goto end;
  }

  b = matrix_sparse_file_scan_by_name(b_name, b_format);
  if (errno)
  {
    perror("Cannot scan the second matrix");
    goto a_free;
  }

  c = matrix_sparse_linear_combination(a, b, alpha, beta);
  if (errno)
  {
    perror("Cannot find the linear combination");
    goto b_free;
  }

  matrix_sparse_file_print(out, c, out_format);
  if (errno)
  {
    perror("Cannot print the linear combination");
    goto c_free;
  }

c_free:
  matrix_sparse_free(c);
b_free:
  matrix_sparse_free(b);
a_free:
  matrix_sparse_free(a);
end:
  return;
}

int main(int argc, char * argv[])
{
  char * a_format, * a_name, * b_format, * b_name, * out_format, * ptr;
  double alpha, beta;

  if (argc != 8)
  {
    errno = EIO;
    perror("Command-line argument list is not of the right format");
    goto end;
  }

  a_name = argv[1];
  a_format = argv[2];
  b_name = argv[3];
  b_format = argv[4];

  alpha = strtod(argv[5], &ptr);
  if (*ptr != '\0')
  {
    errno = EINVAL;
    perror("First coefficient is not a valid number");
    goto end;
  }

  beta = strtod(argv[6], &ptr);
  if (*ptr != '\0')
  {
    errno = EINVAL;
    perror("Second coefficient is not a valid number");
    goto end;
  }

  out_format = argv[7];

  matrix_sparse_linear_combination_file_print(
    stdout, a_name, a_format, b_name, b_format, alpha, beta, out_format);
  if (errno)
  {
    perror("Unsuccessful execution of matrix_sparse_linear_combination");
    goto end;
  }

end:
  return errno;
}
