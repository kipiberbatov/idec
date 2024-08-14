#include <errno.h>
#include <stdlib.h>
#include "matrix_sparse.h"
#include "double.h"

/*
matrix_sparse_multiply_with_diagonal_matrix --raw <matrix_sparse_input> \
--raw <diagonal_matrix_input> --raw > <output>
*/
int main(int argc, char * argv[])
{
  double * d;
  matrix_sparse * a;
  char * a_name, * d_name;
  char * a_format, * d_format, * out_format;

  if (argc != 6)
  {
    fprintf(stderr, "Number of command arguments should be 6\n");
    errno = EINVAL;
    goto end;
  }

  /* scan sparse matrix */
  a_format = argv[1];
  a_name = argv[2];
  a = matrix_sparse_file_scan_by_name(a_name, a_format);
  if (errno)
  {
    fprintf(stderr, "Cannot scan sparse matrix\n");
    goto end;
  }

  /* scan diagonal matrix */
  d_format = argv[3];
  d_name = argv[4];
  d = double_array_file_scan_by_name(d_name, a->cols, d_format);
  if (errno)
  {
    fprintf(stderr, "Cannot scan diagonal matrix\n");
    goto a_free;
  }

  matrix_sparse_multiply_with_diagonal_matrix(a, d);

  out_format = argv[5];
  matrix_sparse_file_print(stdout, a, out_format);

  free(d);
a_free:
  matrix_sparse_free(a);
end:
  return errno;
}
