#include <errno.h>
#include <string.h>
#include "jagged_private.h"

jagged3 * jagged3_fscan(FILE * in, const char * format)
{
  int i;
  jagged3 * arr;
  
  for (i = 0; i < JAGGED3_FSCAN_FORMAT_TOTAL; ++i)
    if (!strcmp(format, jagged3_fscan_format[i]))
    {
      arr = jagged3_fscan_function[i](in);
      if (errno)
      {
        perror("jagged2_fscan - cannot scan input");
        return NULL;
      }
      return arr;
    }
  errno = EINVAL;
  perror(format);
  return NULL;
}
