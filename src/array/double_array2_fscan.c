#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "double_private.h"

double ** double_array2_file_scan(
  FILE * in, int a0,  const int * a1, const char * format)
{
  int i;
  double ** a;
  
  for (i = 0; i < DOUBLE_ARRAY2_file_scan_format_total; ++i)
    if (!strcmp(format, double_array2_file_scan_format[i]))
    {
      a = double_array2_file_scan_function[i](in, a0, a1);
      if (errno)
      {
        fprintf(stderr,
                "double_array2_file_scan - cannot scan a[%d]: %s\n",
                i, strerror(errno));
        return NULL;
      }
      return a;
    }
  errno = EINVAL;
  fprintf(stderr, "double_array2_file_scan - format %s is not supported: %s\n",
          format, strerror(errno));
  return NULL;
}
