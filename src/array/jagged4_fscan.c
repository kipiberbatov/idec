#include <errno.h>
#include <string.h>
#include "jagged_private.h"

jagged4 * jagged4_fscan(FILE * in, const char * format)
{
  int i;
  jagged4 * arr;
  
  for (i = 0; i < JAGGED4_FSCAN_FORMAT_TOTAL; ++i)
    if (!strcmp(format, jagged4_fscan_format[i]))
    {
      arr = jagged4_fscan_function[i](in);
      if (errno)
      {
        perror("jagged4_fscan - cannot scan input");
        return NULL;
      }
      return arr;
    }
  errno = EINVAL;
  perror(format);
  return NULL;
}
