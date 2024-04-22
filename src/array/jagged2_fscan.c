#include <errno.h>
#include <string.h>
#include "jagged_private.h"

jagged2 * jagged2_file_scan(FILE * in, const char * format)
{
  int i;
  jagged2 * arr;
  
  for (i = 0; i < JAGGED2_file_scan_format_total; ++i)
    if (!strcmp(format, jagged2_file_scan_format[i]))
    {
      arr = jagged2_file_scan_function[i](in);
      if (errno)
      {
        perror("jagged2_file_scan - cannot scan input");
        return NULL;
      }
      return arr;
    }
  errno = EINVAL;
  perror(format);
  return NULL;
}
