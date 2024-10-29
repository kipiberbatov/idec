#include <errno.h>
#include "matrix_sparse.h"

int main(int argc, char ** argv)
{
  char * a_format, * a_name, * b_format, * b_name, * out_format;
  matrix_sparse * a, * b, * c;

  if (argc != 6)
  {
    errno = EIO;
    fputs("main - command-line arguments should be 6 in total", stderr);
    goto end;
  }

  a_name = argv[1];
  a_format = argv[2];
  a = matrix_sparse_file_scan_by_name(a_name, a_format);
  if (errno)
  {
    fprintf(stderr, "main - cannot scan the first matrix a in format %s\n",
            a_format);
    goto end;
  }

  b_name = argv[3];
  b_format = argv[4];
  b = matrix_sparse_file_scan_by_name(b_name, b_format);
  if (errno)
  {
    fprintf(stderr, "main - cannot scan the second matrix b in format %s\n",
            b_format);
    goto a_free;
  }

  c = matrix_sparse_product(a, b);
  if (errno)
  {
    fputs("main - cannot find the matrix product c = a . b\n", stderr);
    goto b_free;
  }

  out_format = argv[5];
  matrix_sparse_file_print(stdout, c, out_format);
  if (errno)
  {
    fprintf(stderr, "main - cannot print the result c in format %s\n",
            out_format);
    goto c_free;
  }

c_free:
  matrix_sparse_free(c);
b_free:
  matrix_sparse_free(b);
a_free:
  matrix_sparse_free(a);
end:
  return errno;
}
