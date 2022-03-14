#include <errno.h>
#include <string.h>
#include "matrix_sparse_private.h"

void matrix_sparse_fprint(
  FILE * out, const matrix_sparse * a, const char * format)
{
  int i;
  
  for (i = 0; i < FPRINT_FORMATS_TOTAL; ++i)
    if (!strcmp(format, fprint_formats[i]))
    {
      fprinters[i](out, a);
      if (errno)
      {
        perror("Unsuccessful matrix printing");
        return;
      }
      return;
    }
  errno = EINVAL;
  perror(format);
  return;
}

void matrix_sparse_fprint_array(
  FILE * out, int n, matrix_sparse const * const * a, const char * format)
{
  int i;

  for (i = 0; i < n; ++i)
  {
    matrix_sparse_fprint(out, a[i], format);
    if (errno)
    {
      fprintf(stderr, "Cannot print matrix a[%d]", i);
      perror("");
      return;
    }
    if (i < n - 1)
      fputc('\n', out);
  }
}
