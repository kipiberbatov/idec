#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "int.h"
#include "matrix_sparse.h"

int main(int argc, char ** argv)
{
  int d;
  matrix_sparse ** a, ** b;

  if (argc != 7)
  {
    errno = EINVAL;
    fprintf(stderr, "Number of command line arguments must be 7\n");
    goto end;
  }

  d = int_string_scan(argv[1]);
  if (errno)
  {
    fputs("main: cannot scan dimension\n", stderr);
    goto end;
  }

  a = matrix_sparse_array_file_scan_by_name(argv[3], d, argv[2]);
  if (errno)
  {
    fputs("main: cannot scan a\n", stderr);
    goto end;
  }

  b = matrix_sparse_array_file_scan_by_name(argv[5], d, argv[4]);
  if (errno)
  {
    fputs("main: cannot scan b\n", stderr);
    goto a_free;
  }

  matrix_sparse_laplacian_file_print(stdout, d, a, b, argv[6]);
  if (errno)
  {
    fputs("main: cannot print laplacians\n", stderr);
    goto b_free;
  }

b_free:
  matrix_sparse_array_free(b, d);
a_free:
  matrix_sparse_array_free(a, d);
end:
  return errno;
}
