#include <errno.h>
#include <string.h>

#include "color.h"
#include "double_private.h"

double ** double_array2_file_scan(
  FILE * in, int a0, const int * a1, const char * format)
{
  double ** a;

  if (!strcmp(format, "--raw"))
    a = double_array2_file_scan_raw(in, a0, a1);
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
    fputs("cannot scan input\n", stderr);
  }
  return a;
}
