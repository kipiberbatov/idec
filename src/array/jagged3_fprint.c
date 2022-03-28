#include <errno.h>
#include <string.h>
#include "jagged_private.h"

void jagged3_fprint(FILE * out, const jagged3 * arr, const char * format)
{
  int i;
  
  for (i = 0; i < JAGGED3_FPRINT_FORMAT_TOTAL; ++i)
    if (!strcmp(format, jagged3_fprint_format[i]))
    {
      jagged3_fprint_function[i](out, arr);
      if (errno)
      {
        perror("jagged3_fprint - cannot print arr to out");
        return;
      }
      return;
    }
  errno = EINVAL;
  perror(format);
}
