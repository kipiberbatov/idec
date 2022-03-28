#include <errno.h>
#include <string.h>
#include "double_private.h"

void double_array_fprint(
  FILE * out, int n, const double * a, const char * format)
{
  int i;
  
  for (i = 0; i < DOUBLE_ARRAY_FPRINT_FORMAT_TOTAL; ++i)
    if (!strcmp(format, double_array_fprint_format[i]))
    {
      double_array_fprint_function[i](out, n, a);
      if (errno)
      {
        perror("double_array_fprint - printing failed");
        return;
      }
      return;
    }
  errno = EINVAL;
  fprintf(stderr, "double_array_fprint - format %s is not supported: %s\n",
          format, strerror(errno));
}
