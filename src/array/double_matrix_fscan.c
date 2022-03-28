#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "double_private.h"

double * double_matrix_fscan(FILE * in, int m, int n, const char * format)
{
  int i;
  double * a;
  
  for (i = 0; i < DOUBLE_MATRIX_FSCAN_FORMAT_TOTAL; ++i)
    if (!strcmp(format, double_matrix_fscan_format[i]))
    {
      a = double_matrix_fscan_function[i](in, m, n);
      if (errno)
      {
        perror("double_matrix_fscan - scanning failed");
        return NULL;
      }
      return a;
    }
  errno = EINVAL;
  fprintf(stderr, "double_matrix_fscan - format %s is not supported: %s\n",
          format, strerror(errno));
  return NULL;
}
