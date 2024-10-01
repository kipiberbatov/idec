#include <errno.h>
#include <stdlib.h>
#include "double.h"
#include "matrix_sparse.h"

static void matrix_sparse_linear_solve_file_print(
  FILE * out, const char * a_name, const char * a_format, const char * b_name,
  const char * method)
{
  matrix_sparse * a;
  double * b;
  FILE * b_in;

  a = matrix_sparse_file_scan_by_name(a_name, a_format);
  if (errno)
  {
    perror("Cannot scan the first matrix");
    goto end;
  }

  b_in = fopen(b_name, "r");
  if (errno)
  {
    perror("Cannot open file for reading vector");
    goto end;
  }

  b = double_array_file_scan(b_in, a->rows, "--raw");
  if (errno)
  {
    perror("Cannot scan vector");
    fclose(b_in);
    goto a_free;
  }
  fclose(b_in);

  matrix_sparse_linear_solve(a, b, method);
  if (errno)
  {
    perror("Cannot solve linear equation");
    goto b_free;
  }

  double_array_file_print(out, a->rows, b, "--raw");

b_free:
  free(b);
a_free:
  matrix_sparse_free(a);
end:
  return;
}

int main(int argc, char ** argv)
{
  char * a_format, * a_name, * b_name, * method;

  if (argc != 5)
  {
    errno = EIO;
    perror("Command-line argument list is not of the right format");
    goto end;
  }
  a_name = argv[1];
  a_format = argv[2];
  b_name = argv[3];
  method = argv[4];
  matrix_sparse_linear_solve_file_print(
    stdout, a_name, a_format, b_name, method);
  if (errno)
  {
    perror("Unsuccessful execution of matrix_sparse_linear_solve");
    goto end;
  }
end:
  return errno;
}
