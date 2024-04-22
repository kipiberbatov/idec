#include <errno.h>
#include <string.h>
#include "int_private.h"

int * int_array_file_scan(FILE * in, int n, const char * format)
{
  int * a;

  if (!strcmp(format, "--raw"))
    a = int_array_file_scan_raw(in, n);
  else
  {
    errno = EINVAL;
    fprintf(stderr,
      "int_array_file_scan - format %s is not supported\n", format);
    return NULL;
  }
  
  if (errno)
    fputs("int_array_file_scan - cannot scan input\n", stderr);
  return a;
}
