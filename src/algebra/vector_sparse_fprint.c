#include <errno.h>
#include <string.h>
#include "vector_sparse_private.h"

void vector_sparse_fprint(
  FILE * out, const vector_sparse * a, const char * format)
{
  int i;
  
  for (i = 0; i < VECTOR_SPARSE_FPRINT_FORMAT_TOTAL; ++i)
    if (!strcmp(format, vector_sparse_fprint_format[i]))
    {
      vector_sparse_fprint_function[i](out, a);
      if (errno)
      {
        perror("vector_sparse_fprint - cannot print a");
        return;
      }
      return;
    }
  errno = EINVAL;
  fprintf(stderr, "vector_sparse_fprint - format %s is not supported: %s\n",
          format, strerror(errno));
  return;
}
