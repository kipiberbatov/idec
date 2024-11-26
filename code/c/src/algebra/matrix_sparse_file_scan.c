#include <errno.h>
#include <string.h>

#include "color.h"
#include "matrix_sparse_private.h"

matrix_sparse * matrix_sparse_file_scan(FILE * in, const char * format)
{
  matrix_sparse * a;

  if (!strcmp(format, "--raw"))
    a = matrix_sparse_file_scan_raw(in);
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
  }
  return a;
}
