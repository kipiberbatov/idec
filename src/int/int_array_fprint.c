#include <errno.h>
#include <string.h>
#include "int_private.h"

void int_array_fprint(FILE * out, int n, const int * a, const char * format)
{
  int i;
  
  for (i = 0; i < INT_ARRAY_FPRINT_FORMAT_TOTAL; ++i)
    if (!strcmp(format, int_array_fprint_format[i]))
    {
      int_array_fprint_function[i](out, n, a);
      if (errno)
      {
        perror("int_array_fprint - printing failed");
        return;
      }
      return;
    }
  errno = EINVAL;
  fprintf(stderr, "int_array_fprint - format %s is not supported: %s\n",
          format, strerror(errno));
  return;
}
