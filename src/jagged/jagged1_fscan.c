#include <errno.h>
#include <string.h>
#include "jagged_private.h"

jagged1 * jagged1_fscan(FILE * in, const char * format)
{
  int i;
  jagged1 * arr;
  
  for (i = 0; i < JAGGED1_FSCAN_FORMAT_TOTAL; ++i)
    if (!strcmp(format, jagged1_fscan_format[i]))
    {
      arr = jagged1_fscan_function[i](in);
      if (errno)
      {
        perror("jagged1_fscan - cannot scan input");
        return NULL;
      }
      return arr;
    }
  errno = EINVAL;
  perror(format);
  return NULL;
}
