#include <errno.h>
#include <string.h>
#include "jagged_private.h"

jagged2 * jagged2_fscan(FILE * in, const char * format)
{
  int i;
  jagged2 * arr;
  
  for (i = 0; i < JAGGED2_FSCAN_FORMAT_TOTAL; ++i)
    if (!strcmp(format, jagged2_fscan_format[i]))
    {
      arr = jagged2_fscan_function[i](in);
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
