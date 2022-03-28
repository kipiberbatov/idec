#include <errno.h>
#include <string.h>
#include "jagged_private.h"

void jagged1_fprint(FILE * out, const jagged1 * arr, const char * format)
{
  int i;
  
  for (i = 0; i < JAGGED1_FPRINT_FORMAT_TOTAL; ++i)
    if (!strcmp(format, jagged1_fprint_format[i]))
    {
      jagged1_fprint_function[i](out, arr);
      if (errno)
      {
        perror("jagged1_fprint - cannot print arr to out");
        return;
      }
      return;
    }
  errno = EINVAL;
  perror(format);
}
