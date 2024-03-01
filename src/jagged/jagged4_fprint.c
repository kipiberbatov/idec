#include <errno.h>
#include <string.h>
#include "jagged_private.h"

void jagged4_fprint(FILE * out, const jagged4 * arr, const char * format)
{
  int i;
  
  for (i = 0; i < JAGGED4_FPRINT_FORMAT_TOTAL; ++i)
    if (!strcmp(format, jagged4_fprint_format[i]))
    {
      jagged4_fprint_function[i](out, arr);
      if (errno)
      {
        perror("jagged4_fprint - cannot print arr to out");
        return;
      }
      return;
    }
  errno = EINVAL;
  perror(format);
}
