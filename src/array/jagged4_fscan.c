#include <errno.h>
#include <string.h>
#include "jagged_private.h"

jagged4 * jagged4_file_scan(FILE * in, const char * format)
{
  int i;
  jagged4 * arr;
  
  for (i = 0; i < JAGGED4_file_scan_format_total; ++i)
    if (!strcmp(format, jagged4_file_scan_format[i]))
    {
      arr = jagged4_file_scan_function[i](in);
      if (errno)
      {
        perror("jagged4_file_scan - cannot scan input");
        return NULL;
      }
      return arr;
    }
  errno = EINVAL;
  perror(format);
  return NULL;
}
