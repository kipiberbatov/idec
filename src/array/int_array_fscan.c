#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "int_private.h"

int * int_array_file_scan(FILE * in, int n, const char * format)
{
  int i;
  int * a;
  
  for (i = 0; i < INT_ARRAY_file_scan_format_total; ++i)
    if (!strcmp(format, int_array_file_scan_format[i]))
    {
      a = int_array_file_scan_function[i](in, n);
      if (errno)
      {
        perror("int_array_file_scan - scanning failed");
        return NULL;
      }
      return a;
    }
  errno = EINVAL;
  fprintf(stderr, "int_array_file_scan - format %s is not supported: %s\n",
          format, strerror(errno));
  return NULL;
}
