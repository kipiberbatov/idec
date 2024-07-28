#include <errno.h>
#include <stdlib.h>
#include "matrix_sparse.h"

static void matrix_sparse_copy_file_print(
  FILE * out, const char * a_name, const char * a_format,
  const char * out_format)
{
  matrix_sparse * a, * b;

  a = matrix_sparse_file_scan_by_name(a_name, a_format);
  if (errno)
  {
    perror("Cannot scan input matrix from the specified file and format");
    goto end;
  }
  b = matrix_sparse_copy(a);
  if (errno)
  {
    perror("Cannot copy input matrix");
    goto a_free;
  }
  matrix_sparse_file_print(out, b, out_format);
  if (errno)
  {
    perror("Cannot print the copy in the specified format");
    goto b_free;
  }
b_free:
  matrix_sparse_free(b);
a_free:
  matrix_sparse_free(a);
end:
  return;
}

int main(int argc, char * argv[])
{
  char * a_format, * a_name, * out_format;

  if (argc != 4)
  {
    errno = EIO;
    perror("There should be exactly 4 command line arguments");
    goto end;
  }
  a_format = argv[1];
  a_name = argv[2];
  out_format = argv[3];
  matrix_sparse_copy_file_print(stdout, a_name, a_format, out_format);
  if (errno)
  {
    perror("Unsuccessful execution of matrix_sparse_copy");
    goto end;
  }
end:
  return errno;
}
