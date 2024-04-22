#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_sparse_private.h"

matrix_sparse * matrix_sparse_file_scan(FILE * in, const char * format)
{
  int i;
  matrix_sparse * a;
  
  for (i = 0; i < MATRIX_SPARSE_file_scan_format_total; ++i)
    if (!strcmp(format, matrix_sparse_file_scan_format[i]))
    {
      a = matrix_sparse_file_scan_function[i](in);
      if (errno)
      {
        perror("matrix_sparse_file_scan - cannot scan a");
        return NULL;
      }
      return a;
    }
  errno = EINVAL;
  fprintf(stderr, "matrix_sparse_file_scan - format %s is not supported: %s\n",
          format, strerror(errno));
  return NULL;
}
