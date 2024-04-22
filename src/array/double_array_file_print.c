#include <errno.h>
#include <string.h>
#include "double_private.h"

void double_array_file_print(
  FILE * out, int n, const double * a, const char * format)
{
  int i;
  
  for (i = 0; i < DOUBLE_ARRAY_file_print_format_total; ++i)
    if (!strcmp(format, double_array_file_print_format[i]))
    {
      double_array_file_print_function[i](out, n, a);
      if (errno)
      {
        perror("double_array_file_print - printing failed");
        return;
      }
      return;
    }
  errno = EINVAL;
  fprintf(stderr, "double_array_file_print - format %s is not supported: %s\n",
          format, strerror(errno));
}
