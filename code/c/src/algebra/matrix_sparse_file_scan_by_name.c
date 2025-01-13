#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "matrix_sparse.h"

matrix_sparse * matrix_sparse_file_scan_by_name(
  const char * name, const char * format)
{
  FILE * in;
  matrix_sparse * a = NULL;

  in = fopen(name, "r");
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open file %s%s%s: %s%s%s\n",
      color_variable, name, color_none,
      color_stdlib, strerror(errno), color_none);
    goto end;
  }

  a = matrix_sparse_file_scan(in, format);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan sparse matrix in format %s%s%s\n",
      color_variable, name, color_none);
    goto in_close;
  }

in_close:
  fclose(in);
end:
  return a;
}
