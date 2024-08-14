#include <errno.h>
#include <string.h>
#include "matrix_sparse_private.h"

matrix_sparse * matrix_sparse_file_scan(FILE * in, const char * format)
{
  matrix_sparse * a;

  if (!strcmp(format, "--raw"))
    a = matrix_sparse_file_scan_raw(in);
  else
  {
    errno = EINVAL;
    fprintf(stderr,
      "matrix_sparse_file_scan - format %s is not supported\n", format);
    return NULL;
  }

  if (errno)
    fputs("matrix_sparse_file_scan - cannot scan input\n", stderr);
  return a;
}
