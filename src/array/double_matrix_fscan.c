#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "double_private.h"

double * double_matrix_file_scan(FILE * in, int m, int n, const char * format)
{
  int i;
  double * a;
  
  for (i = 0; i < DOUBLE_MATRIX_file_scan_format_total; ++i)
    if (!strcmp(format, double_matrix_file_scan_format[i]))
    {
      a = double_matrix_file_scan_function[i](in, m, n);
      if (errno)
      {
        perror("double_matrix_file_scan - scanning failed");
        return NULL;
      }
      return a;
    }
  errno = EINVAL;
  fprintf(stderr, "double_matrix_file_scan - format %s is not supported: %s\n",
          format, strerror(errno));
  return NULL;
}
