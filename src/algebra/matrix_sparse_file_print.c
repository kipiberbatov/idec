#include <errno.h>
#include <string.h>
#include "matrix_sparse_private.h"

void matrix_sparse_file_print(
  FILE * out, const matrix_sparse * a, const char * format)
{
  int i;
  
  for (i = 0; i < MATRIX_SPARSE_file_print_format_total; ++i)
    if (!strcmp(format, matrix_sparse_file_print_format[i]))
    {
      matrix_sparse_file_print_function[i](out, a);
      if (errno)
      {
        perror("matrix_sparse_file_print - cannot print a");
        return;
      }
      return;
    }
  errno = EINVAL;
  fprintf(stderr,
          "matrix_sparse_file_print - format %s is not supported\n", format);
  return;
}
