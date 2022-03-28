#include <errno.h>
#include <string.h>
#include "jagged_private.h"

void jagged2_fprint(FILE * out, const jagged2 * arr, const char * format)
{
  int i;
  
  for (i = 0; i < JAGGED2_FPRINT_FORMAT_TOTAL; ++i)
    if (!strcmp(format, jagged2_fprint_format[i]))
    {
      jagged2_fprint_function[i](out, arr);
      if (errno)
      {
        perror("jagged2_fprint - cannot print arr to out");
        return;
      }
      return;
    }
  errno = EINVAL;
  perror(format);
}
