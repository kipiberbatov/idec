#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "matrix_sparse.h"

matrix_sparse ** matrix_sparse_array_file_scan_by_name(
  const char * name, int a0, const char * format)
{
  FILE * in;
  matrix_sparse ** a = NULL;

  in = fopen(name, "r");
  if (errno)
  {
    fprintf(stderr,
      "matrix_sparse_array_file_scan_by_name: cannot open file %s: %s\n",
      name, strerror(errno));
    goto end;
  }

  a = matrix_sparse_array_file_scan(in, a0, format);
  if (errno)
  {
    fprintf(stderr,
      "matrix_sparse_array_file_scan_by_name: cannot scan file %s", name);
    goto in_close;
  }

in_close:
  fclose(in);
end:
  return a;
}
