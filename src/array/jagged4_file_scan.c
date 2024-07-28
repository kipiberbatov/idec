#include <errno.h>
#include <string.h>
#include "jagged_private.h"

jagged4 * jagged4_file_scan(FILE * in, const char * format)
{
  jagged4 * arr;

  if (!strcmp(format, "--raw"))
    arr = jagged4_file_scan_raw(in);
  else
  {
    errno = EINVAL;
    fprintf(stderr, "jagged4_file_scan - format %s is not supported\n", format);
    return NULL;
  }

  if (errno)
    fputs("jagged4_file_scan - cannot scan input\n", stderr);
  return arr;
}
