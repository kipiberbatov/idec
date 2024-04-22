#include <errno.h>
#include <string.h>
#include "double_private.h"

double ** double_array2_file_scan(
  FILE * in, int a0, const int * a1, const char * format)
{
  double ** a;

  if (!strcmp(format, "--raw"))
    a = double_array2_file_scan_raw(in, a0, a1);
  else
  {
    errno = EINVAL;
    fprintf(stderr,
      "double_array2_file_scan - format %s is not supported\n", format);
    return NULL;
  }
  
  if (errno)
    fputs("double_array2_file_scan - cannot scan input\n", stderr);
  return a;
}
