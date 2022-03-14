#include <errno.h>
#include <stdlib.h>
#include "matrix_sparse.h"

static void matrix_sparse_product_fprint(
  FILE * out, const char * a_name, const char * a_format, const char * b_name,
  const char * b_format, const char * out_format)
{
  matrix_sparse * a, * b, * c;

  a = matrix_sparse_fscan_by_name(a_name, a_format);
  if (errno)
  {
    perror("Cannot scan the first matrix");
    goto end;
  }
  b = matrix_sparse_fscan_by_name(b_name, b_format);
  if (errno)
  {
    perror("Cannot scan the second matrix");
    goto a_free;
  }
  c = matrix_sparse_product(a, b);
  if (errno)
  {
    perror("Cannot find the matrix product");
    goto b_free;
  }
  matrix_sparse_fprint(out, c, out_format);
  if (errno)
  {
    perror("Cannot print the matrix product");
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
  char * a_format, * a_name, * b_format, * b_name, * out_format;
  
  if (argc != 6)
  {
    errno = EIO;
    perror("Command-line argument list is not of the right format");
    goto end;
  }
  a_name = argv[1];
  a_format = argv[2];
  b_name = argv[3];
  b_format = argv[4];
  out_format = argv[5];
  matrix_sparse_product_fprint(
    stdout, a_name, a_format, b_name, b_format, out_format);
  if (errno)
  {
    perror("Unsuccessful execution of matrix_sparse_product");
    goto end;
  }
end:
  return errno;
}
