#include <errno.h>
#include <string.h>
#include "double_private.h"

void double_matrix_fprint(
  FILE * out, int m, int n, const double * a, const char * format)
{
  int i;
  
  for (i = 0; i < DOUBLE_MATRIX_FPRINT_FORMAT_TOTAL; ++i)
    if (!strcmp(format, double_matrix_fprint_format[i]))
    {
      double_matrix_fprint_function[i](out, m, n, a);
      if (errno)
      {
        perror("double_matrix_fprint - printing failed");
        return;
      }
      return;
    }
  errno = EINVAL;
  fprintf(stderr, "double_matrix_fprint - format %s is not supported: %s\n",
          format, strerror(errno));
}
