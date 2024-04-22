#include <errno.h>
#include <string.h>
#include "double_private.h"

void double_matrix_file_print(
  FILE * out, int m, int n, const double * a, const char * format)
{
  int i;
  
  for (i = 0; i < DOUBLE_MATRIX_file_print_format_total; ++i)
    if (!strcmp(format, double_matrix_file_print_format[i]))
    {
      double_matrix_file_print_function[i](out, m, n, a);
      if (errno)
      {
        perror("double_matrix_file_print - printing failed");
        return;
      }
      return;
    }
  errno = EINVAL;
  fprintf(stderr, "double_matrix_file_print - format %s is not supported: %s\n",
          format, strerror(errno));
}
