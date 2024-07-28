#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "vector_sparse.h"

vector_sparse ** vector_sparse_array_file_scan_by_name(
  const char * name, int a0, const char * format)
{
  FILE * in;
  vector_sparse ** a = NULL;

  in = fopen(name, "r");
  if (errno)
  {
    fprintf(stderr,
      "vector_sparse_array_file_scan_by_name: cannot open file %s: %s\n",
      name, strerror(errno));
    goto end;
  }

  a = vector_sparse_array_file_scan(in, a0, format);
  if (errno)
  {
    fprintf(stderr,
      "vector_sparse_array_file_scan_by_name: cannot scan file %s", name);
    goto in_close;
  }

in_close:
  fclose(in);
end:
  return a;
}
