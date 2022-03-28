#include <errno.h>
#include <string.h>
#include "matrix_sparse_private.h"

void matrix_sparse_fprint(
  FILE * out, const matrix_sparse * a, const char * format)
{
  int i;
  
  for (i = 0; i < MATRIX_SPARSE_FPRINT_FORMAT_TOTAL; ++i)
    if (!strcmp(format, matrix_sparse_fprint_format[i]))
    {
      matrix_sparse_fprint_function[i](out, a);
      if (errno)
      {
        perror("matrix_sparse_fprint - cannot print a");
        return;
      }
      return;
    }
  errno = EINVAL;
  fprintf(stderr,
          "matrix_sparse_fprint - format %s is not supported\n", format);
  return;
}
