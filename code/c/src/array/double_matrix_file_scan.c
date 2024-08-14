#include <errno.h>
#include <string.h>
#include "double_private.h"

double * double_matrix_file_scan(FILE * in, int m, int n, const char * format)
{
  double * a;

  if (!strcmp(format, "--raw"))
    a = double_matrix_file_scan_raw(in, m, n);
  else
  {
    errno = EINVAL;
    fprintf(stderr,
      "double_matrix_file_scan - format %s is not supported\n", format);
    return NULL;
  }

  if (errno)
    fputs("double_matrix_file_scan - cannot scan input\n", stderr);
  return a;
}
