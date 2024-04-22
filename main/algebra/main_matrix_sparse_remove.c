#include <errno.h>
#include "jagged.h"
#include "matrix_sparse.h"

static void matrix_sparse_remove_file_print(
  FILE * out, const matrix_sparse * a, const jagged1 * rows,
  const jagged1 * cols)
{
  matrix_sparse * b;
  
  b = matrix_sparse_remove(a, rows, cols);
  if (errno)
  {
    perror("Problem in matrix_sparse scanning");
    return;
  }
  matrix_sparse_file_print(out, b, "--raw");
  matrix_sparse_free(b);
}

int main()
{
  matrix_sparse * a;
  jagged1 * rows, * cols;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  
  a = matrix_sparse_file_scan(in, "--raw");
  if (errno)
  {
    fputs("main - cannot scan matrix a\n", stderr);
    goto end;
  }
  
  rows = jagged1_file_scan(in, "--raw");
  if (errno)
  {
    fputs("main - cannot scan rows\n", stderr);
    goto a_free;
  }
  
  cols = jagged1_file_scan(in, "--raw");
  if (errno)
  {
    fputs("main - cannot scan cols a\n", stderr);
    goto rows_free;
  }
  
  matrix_sparse_remove_file_print(out, a, rows, cols);
  if (errno)
  {
    fputs("main - cannot remove rows and cols from a and print\n", stderr);
    goto cols_free;
  }
  
cols_free:
  jagged1_free(cols);
rows_free:
  jagged1_free(rows);
a_free:
  matrix_sparse_free(a);
end:
  return errno;
}
