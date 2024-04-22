#include <errno.h>
#include <string.h>
#include "jagged_private.h"

jagged3 * jagged3_file_scan(FILE * in, const char * format)
{
  jagged3 * arr;

  if (!strcmp(format, "--raw"))
    arr = jagged3_file_scan_raw(in);
  else
  {
    errno = EINVAL;
    fprintf(stderr, "jagged3_file_scan - format %s is not supported\n", format);
    return NULL;
  }
  
  if (errno)
    fputs("jagged3_file_scan - cannot scan input\n", stderr);
  return arr;
}
