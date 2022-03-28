#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "double_private.h"

double * double_array_fscan(FILE * in, int n, const char * format)
{
  int i;
  double * a;
  
  for (i = 0; i < DOUBLE_ARRAY_FSCAN_FORMAT_TOTAL; ++i)
    if (!strcmp(format, double_array_fscan_format[i]))
    {
      a = double_array_fscan_function[i](in, n);
      if (errno)
      {
        perror("double_array_fscan - cannot scan a");
        return NULL;
      }
      return a;
    }
  errno = EINVAL;
  fprintf(stderr, "double_array_fscan - format %s is not supported: %s\n",
          format, strerror(errno));
  return NULL;
}
