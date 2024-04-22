#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "double_private.h"

double * double_array_file_scan(FILE * in, int n, const char * format)
{
  int i;
  double * a;
  
  for (i = 0; i < DOUBLE_ARRAY_file_scan_format_total; ++i)
    if (!strcmp(format, double_array_file_scan_format[i]))
    {
      a = double_array_file_scan_function[i](in, n);
      if (errno)
      {
        perror("double_array_file_scan - cannot scan a");
        return NULL;
      }
      return a;
    }
  errno = EINVAL;
  fprintf(stderr, "double_array_file_scan - format %s is not supported: %s\n",
          format, strerror(errno));
  return NULL;
}
