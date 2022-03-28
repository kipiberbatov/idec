#include <errno.h>
#include "matrix_sparse.h"

static void matrix_sparse_part_fprint(FILE * out, const matrix_sparse * a)
{
  int i, j;
  double k;
  
  for (i = 0; i < a->rows; ++i)
  {
    for (j = 0; j < a->cols - 1; ++j)
    {
      k = matrix_sparse_part(a, i, j);
      fprintf(out, "%g ", k);
    }
    k = matrix_sparse_part(a, i, j);
    fprintf(out, "%g\n", k);
  }
}

int main()
{
  matrix_sparse * a;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  a = matrix_sparse_fscan(in, "--raw");
  if (errno)
  {
    perror("Problem in matrix_sparse scanning");
    goto a_free;
  }
  matrix_sparse_part_fprint(out, a);
a_free:
  matrix_sparse_free(a);
  return errno;
}
