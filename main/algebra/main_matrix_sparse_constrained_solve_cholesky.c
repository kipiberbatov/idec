#include <errno.h>
#include <stdlib.h>
#include "matrix_sparse.h"
#include "double.h"

static void matrix_sparse_constrained_solve_cholesky_file_print(
  FILE * out, const matrix_sparse * a, const double * b, const jagged1 * rows)
{
  double * x;

  x = matrix_sparse_constrained_solve_cholesky(a, b, rows);
  if (errno)
  {
    fputs("matrix_sparse_constrained_solve_cholesky_file_print - cannot find x\n",
          stderr);
    return;
  }
  fprintf(out, "%d\n", a->rows);
  double_array_file_print(out, a->rows, x, "--raw");
  free(x);
}

int main()
{
  int b_m;
  double * b;
  jagged1 * rows;
  matrix_sparse * a;
  FILE * in, * out;

  out = stdout;
  in = stdin;
  fscanf(in, "%d", &b_m);

  b = double_array_file_scan(in, b_m, "--raw");
  if (errno)
  {
    fputs("main - cannot scan right-hand side b\n", stderr);
    goto end;
  }

  rows = jagged1_file_scan(in, "--raw");
  if (errno)
  {
    fputs("main - cannot scan rows for deletion\n", stderr);
    goto b_free;
  }

  a = matrix_sparse_file_scan(in, "--raw");
  if (errno)
  {
    fputs("main - cannot scan left-hand side a\n", stderr);
    goto rows_free;
  }

  matrix_sparse_constrained_solve_cholesky_file_print(out, a, b, rows);
  if (errno)
  {
    fputs("main - cannot restrict, solve and print\n", stderr);
    goto a_free;
  }

a_free:
  matrix_sparse_free(a);
rows_free:
  jagged1_free(rows);
b_free:
  free(b);
end:
  return errno;
}
