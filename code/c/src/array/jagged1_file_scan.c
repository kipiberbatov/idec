#include <errno.h>
#include <string.h>

#include "color.h"
#include "jagged_private.h"

jagged1 * jagged1_file_scan(FILE * in, const char * format)
{
  jagged1 * arr;

  if (!strcmp(format, "--raw"))
    arr = jagged1_file_scan_raw(in);
  else
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "format %s is not supported\n", format);
    errno = EINVAL;
    return NULL;
  }

  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan input in format %s\n", format);
    return NULL;
  }

  return arr;
}
