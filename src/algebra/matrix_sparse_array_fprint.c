#include <errno.h>
#include <string.h>
#include "matrix_sparse.h"

void matrix_sparse_array_fprint(
  FILE * out, int n, matrix_sparse ** a, const char * format)
{
  int i;

  for (i = 0; i < n; ++i)
  {
    matrix_sparse_fprint(out, a[i], format);
    if (errno)
    {
      fprintf(stderr,
              "matrix_sparse_array_fprint - cannot print a[%d]: %s\n",
              i, strerror(errno));
      return;
    }
    if (i < n - 1)
      fputc('\n', out);
  }
}
